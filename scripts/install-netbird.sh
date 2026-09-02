#!/usr/bin/env bash
#
# install-netbird.sh — idempotent NetBird (https://netbird.io) client install
# and enrolment for Debian/Ubuntu container and micro-VM environments.
#
# Follows the upstream Linux install documented at
# https://docs.netbird.io/get-started/install/linux, with two differences that
# matter in sandboxed environments:
#
#   * Re-running the script converges instead of failing. The upstream one-liner
#     aborts with "NetBird seems to be installed already".
#   * The daemon is supervised directly when systemd is not PID 1, so the script
#     works in containers and micro-VMs where `netbird service install` cannot
#     register a unit.
#
# Usage:
#   NETBIRD_SETUP_KEY=<key> ./install-netbird.sh
#   ./install-netbird.sh --setup-key-file /run/secrets/netbird_key
#   ./install-netbird.sh --status
#
# Run `./install-netbird.sh --help` for all options.

set -euo pipefail

readonly BIN_PATH="/usr/bin/netbird"
readonly CONFIG_DIR="/etc/netbird"
readonly STATE_FILE="${CONFIG_DIR}/install.conf"
readonly KEYRING="/usr/share/keyrings/netbird-archive-keyring.gpg"
readonly APT_LIST="/etc/apt/sources.list.d/netbird.list"
readonly APT_KEY_URL="https://pkgs.netbird.io/debian/public.key"
readonly APT_REPO_LINE="deb [signed-by=${KEYRING}] https://pkgs.netbird.io/debian stable main"
readonly RELEASES_URL="https://pkgs.netbird.io/releases/latest"
readonly GITHUB_RELEASES="https://github.com/netbirdio/netbird/releases/download"
readonly GITHUB_API="https://api.github.com/repos/netbirdio/netbird/releases/latest"
readonly GITHUB_LATEST="https://github.com/netbirdio/netbird/releases/latest/download/version"
readonly DAEMON_SOCKET="/var/run/netbird.sock"
readonly DAEMON_PIDFILE="/run/netbird-daemon.pid"

# Configuration, overridable by environment or flag.
SETUP_KEY="${NETBIRD_SETUP_KEY:-}"
SETUP_KEY_FILE="${NETBIRD_SETUP_KEY_FILE:-}"
MANAGEMENT_URL="${NETBIRD_MANAGEMENT_URL:-https://api.netbird.io:443}"
INSTALL_METHOD="${NETBIRD_INSTALL_METHOD:-auto}"   # auto | apt | binary
WANTED_VERSION="${NETBIRD_VERSION:-latest}"        # latest | vX.Y.Z
NB_HOSTNAME="${NETBIRD_HOSTNAME:-}"
ALLOW_SERVER_SSH="${NETBIRD_ALLOW_SERVER_SSH:-false}"
SKIP_CONNECT="${NETBIRD_SKIP_CONNECT:-false}"
DAEMON_LOG="${NETBIRD_LOG_FILE:-/var/log/netbird/daemon.log}"
STATUS_ONLY=false

TMPDIR_SELF=""
CHANGED=false

log()  { printf '\033[0;32m[netbird]\033[0m %s\n' "$*"; }
warn() { printf '\033[0;33m[netbird]\033[0m %s\n' "$*" >&2; }
die()  { printf '\033[0;31m[netbird]\033[0m %s\n' "$*" >&2; exit 1; }
note_change() { CHANGED=true; }

cleanup() {
  if [ -n "$TMPDIR_SELF" ] && [ -d "$TMPDIR_SELF" ]; then
    rm -rf "$TMPDIR_SELF"
  fi
  return 0
}
trap cleanup EXIT

usage() {
  sed -n '3,20p' "$0" | sed 's/^# \{0,1\}//'
  cat <<'EOF'

Options:
  --setup-key KEY          Setup key. Prefer --setup-key-file or the environment;
                           a key on the command line is visible in `ps`.
  --setup-key-file PATH    Read the setup key from PATH (first line).
  --management-url URL     Management server. Default https://api.netbird.io:443
  --method auto|apt|binary Install source. Default auto (apt when available).
  --version latest|vX.Y.Z  Version to install in binary mode. Default latest.
  --hostname NAME          Peer name to register. Default: the system hostname.
  --allow-server-ssh       Keep the host's own SSH server reachable over NetBird.
  --skip-connect           Install and start the daemon, do not enrol.
  --status                 Report current state and exit without changing anything.
  -h, --help               Show this help.

Environment equivalents: NETBIRD_SETUP_KEY, NETBIRD_SETUP_KEY_FILE,
NETBIRD_MANAGEMENT_URL, NETBIRD_INSTALL_METHOD, NETBIRD_VERSION,
NETBIRD_HOSTNAME, NETBIRD_ALLOW_SERVER_SSH, NETBIRD_SKIP_CONNECT,
NETBIRD_LOG_FILE.

Exit codes: 0 success or already converged, 1 error, 2 bad usage.
EOF
}

parse_args() {
  while [ $# -gt 0 ]; do
    case "$1" in
      --setup-key)       SETUP_KEY="${2:-}"; shift 2 ;;
      --setup-key-file)  SETUP_KEY_FILE="${2:-}"; shift 2 ;;
      --management-url)  MANAGEMENT_URL="${2:-}"; shift 2 ;;
      --method)          INSTALL_METHOD="${2:-}"; shift 2 ;;
      --version)         WANTED_VERSION="${2:-}"; shift 2 ;;
      --hostname)        NB_HOSTNAME="${2:-}"; shift 2 ;;
      --allow-server-ssh) ALLOW_SERVER_SSH=true; shift ;;
      --skip-connect)    SKIP_CONNECT=true; shift ;;
      --status)          STATUS_ONLY=true; shift ;;
      -h|--help)         usage; exit 0 ;;
      *) usage >&2; die "unknown argument: $1" ;;
    esac
  done

  case "$INSTALL_METHOD" in auto|apt|binary) ;; *) die "--method must be auto, apt or binary" ;; esac
  case "$WANTED_VERSION" in latest|v[0-9]*) ;; *) die "--version must be 'latest' or a vX.Y.Z tag" ;; esac
}

require_root() {
  [ "$(id -u)" -eq 0 ] || die "must run as root (try: sudo -E $0 ...)"
}

resolve_setup_key() {
  if [ -n "$SETUP_KEY_FILE" ]; then
    [ -r "$SETUP_KEY_FILE" ] || die "setup key file not readable: $SETUP_KEY_FILE"
    SETUP_KEY="$(head -n 1 "$SETUP_KEY_FILE" | tr -d '[:space:]')"
  fi
  SETUP_KEY="$(printf '%s' "$SETUP_KEY" | tr -d '[:space:]')"
}

detect_arch() {
  case "$(uname -m)" in
    x86_64|amd64)  echo amd64 ;;
    aarch64|arm64) echo arm64 ;;
    armv7l|armv6l) echo armv6 ;;
    i?86|x86)      echo 386 ;;
    *) die "unsupported architecture: $(uname -m)" ;;
  esac
}

# systemd must be PID 1 for `netbird service install` to register a unit.
has_systemd() {
  [ -d /run/systemd/system ] || return 1
  command -v systemctl >/dev/null 2>&1 || return 1
  [ "$(cat /proc/1/comm 2>/dev/null || echo '')" = "systemd" ]
}

installed_version() {
  [ -x "$BIN_PATH" ] || { echo ""; return 0; }
  "$BIN_PATH" version 2>/dev/null | tr -d 'v[:space:]' || echo ""
}

# ---------------------------------------------------------------- prerequisites

ensure_prereqs() {
  local missing=()
  command -v curl >/dev/null 2>&1 || missing+=(curl)
  command -v tar  >/dev/null 2>&1 || missing+=(tar)
  if [ "$INSTALL_METHOD" = apt ]; then
    command -v gpg >/dev/null 2>&1 || missing+=(gnupg)
    [ -e /etc/ssl/certs/ca-certificates.crt ] || missing+=(ca-certificates)
  fi
  [ ${#missing[@]} -eq 0 ] && return 0

  log "installing prerequisites: ${missing[*]}"
  if command -v apt-get >/dev/null 2>&1; then
    DEBIAN_FRONTEND=noninteractive apt-get update -qq
    DEBIAN_FRONTEND=noninteractive apt-get install -y -qq "${missing[@]}"
  else
    die "missing prerequisites and no apt-get to install them: ${missing[*]}"
  fi
  note_change
}

# WireGuard needs a TUN device. Present in most images; absent in some minimal
# containers, where it can be recreated if the host allows mknod.
ensure_tun() {
  if [ -c /dev/net/tun ]; then
    return 0
  fi
  log "creating /dev/net/tun"
  mkdir -p -m 755 /dev/net
  if ! mknod /dev/net/tun c 10 200 2>/dev/null; then
    die "/dev/net/tun is missing and cannot be created. Run the container with --device /dev/net/tun --cap-add NET_ADMIN."
  fi
  chmod 0666 /dev/net/tun
  note_change
}

# ------------------------------------------------------------------ apt install

apt_repo_configured() {
  [ -s "$KEYRING" ] || return 1
  [ -f "$APT_LIST" ] || return 1
  grep -qxF "$APT_REPO_LINE" "$APT_LIST"
}

configure_apt_repo() {
  if apt_repo_configured; then
    log "apt repository already configured"
    return 0
  fi

  log "configuring the NetBird apt repository"
  # Superseded Wiretrustee-era entries would shadow the current repo.
  rm -f /etc/apt/sources.list.d/wiretrustee.list \
        /etc/apt/trusted.gpg.d/wiretrustee.gpg \
        /usr/share/keyrings/wiretrustee-archive-keyring.gpg

  TMPDIR_SELF="${TMPDIR_SELF:-$(mktemp -d)}"
  curl -fsSL --retry 3 --retry-delay 2 "$APT_KEY_URL" -o "$TMPDIR_SELF/netbird.key" \
    || die "could not download the repository signing key from $APT_KEY_URL"
  gpg --batch --yes --dearmor -o "$TMPDIR_SELF/netbird.gpg" "$TMPDIR_SELF/netbird.key" \
    || die "could not dearmor the repository signing key"
  install -m 0644 "$TMPDIR_SELF/netbird.gpg" "$KEYRING"

  printf '%s\n' "$APT_REPO_LINE" > "$APT_LIST"
  chmod 0644 "$APT_LIST"

  DEBIAN_FRONTEND=noninteractive apt-get update -qq
  note_change
}

install_via_apt() {
  configure_apt_repo

  if dpkg -s netbird >/dev/null 2>&1 && [ -x "$BIN_PATH" ]; then
    log "netbird package already installed (version $(installed_version))"
    return 0
  fi

  log "installing the netbird package"
  DEBIAN_FRONTEND=noninteractive apt-get install -y -qq netbird
  note_change
}

# --------------------------------------------------------------- binary install

resolve_latest_version() {
  local tag=""
  tag="$(curl -fsSL --retry 3 --retry-delay 2 "$RELEASES_URL" 2>/dev/null \
        | grep -Eo '"tag_name":[[:space:]]*"v[0-9]+\.[0-9]+\.[0-9]+"' \
        | grep -Eo 'v[0-9]+\.[0-9]+\.[0-9]+' | tail -n 1)" || true
  if [ -z "$tag" ]; then
    tag="$(curl -fsSL --retry 3 --retry-delay 2 "$GITHUB_API" 2>/dev/null \
          | grep -Eo '"tag_name":[[:space:]]*"v[0-9]+\.[0-9]+\.[0-9]+"' \
          | grep -Eo 'v[0-9]+\.[0-9]+\.[0-9]+' | tail -n 1)" || true
  fi
  if [ -z "$tag" ]; then
    # Last resort: the /releases/latest/download redirect resolves the tag with
    # no API quota and no token. The final 404 is expected; only the URL matters.
    tag="$(curl -sSL -o /dev/null -w '%{url_effective}' --max-time 30 \
          "$GITHUB_LATEST" 2>/dev/null | grep -Eo 'v[0-9]+\.[0-9]+\.[0-9]+' | tail -n 1)" || true
  fi
  [ -n "$tag" ] || die "could not resolve the latest NetBird release; pin one with --version vX.Y.Z"
  printf '%s' "$tag"
}

install_via_binary() {
  local arch tag version tarball url current
  arch="$(detect_arch)"

  if [ "$WANTED_VERSION" = latest ]; then
    tag="$(resolve_latest_version)"
  else
    tag="$WANTED_VERSION"
  fi
  version="${tag#v}"

  current="$(installed_version)"
  if [ -n "$current" ] && [ "$current" = "$version" ]; then
    log "netbird $version already installed at $BIN_PATH"
    return 0
  fi

  tarball="netbird_${version}_linux_${arch}.tar.gz"
  url="${GITHUB_RELEASES}/${tag}/${tarball}"
  TMPDIR_SELF="${TMPDIR_SELF:-$(mktemp -d)}"

  log "downloading $tarball"
  curl -fsSL --retry 3 --retry-delay 2 -o "$TMPDIR_SELF/$tarball" "$url" \
    || die "download failed: $url"

  # Release checksums are published alongside the tarballs; verify when present.
  if curl -fsSL --retry 2 -o "$TMPDIR_SELF/checksums.txt" \
       "${GITHUB_RELEASES}/${tag}/netbird_${version}_checksums.txt" 2>/dev/null; then
    if grep -q " ${tarball}\$" "$TMPDIR_SELF/checksums.txt"; then
      ( cd "$TMPDIR_SELF" && grep " ${tarball}\$" checksums.txt | sha256sum -c - >/dev/null ) \
        || die "checksum mismatch for $tarball; refusing to install"
      log "checksum verified"
    else
      warn "no checksum entry for $tarball; continuing without verification"
    fi
  else
    warn "checksums file unavailable; continuing without verification"
  fi

  tar -xzf "$TMPDIR_SELF/$tarball" -C "$TMPDIR_SELF" netbird
  # Replace atomically so a running daemon keeps its open inode until restarted.
  install -m 0755 "$TMPDIR_SELF/netbird" "${BIN_PATH}.new"
  mv -f "${BIN_PATH}.new" "$BIN_PATH"
  log "installed netbird $version"
  note_change
}

record_state() {
  mkdir -p "$CONFIG_DIR"
  printf 'package_manager=%s\n' "$1" > "$STATE_FILE"
  chmod 0644 "$STATE_FILE"
}

# ------------------------------------------------------------------ daemon

daemon_responding() {
  [ -x "$BIN_PATH" ] || return 1
  local out
  out="$("$BIN_PATH" status 2>&1)" || true
  ! printf '%s' "$out" | grep -qi 'failed to connect to daemon'
}

wait_for_daemon() {
  local i
  for i in $(seq 1 30); do
    daemon_responding && return 0
    sleep 1
  done
  return 1
}

start_daemon_systemd() {
  if systemctl is-active --quiet netbird 2>/dev/null; then
    log "netbird service already active"
    return 0
  fi
  log "registering and starting the netbird systemd service"
  "$BIN_PATH" service install >/dev/null 2>&1 || true   # already-installed is fine
  "$BIN_PATH" service start   >/dev/null 2>&1 || systemctl start netbird
  note_change
}

# Containers and micro-VMs where PID 1 is not systemd: supervise the daemon
# directly and keep a pidfile so re-runs do not start a second copy.
start_daemon_supervised() {
  if [ -f "$DAEMON_PIDFILE" ]; then
    local pid
    pid="$(cat "$DAEMON_PIDFILE" 2>/dev/null || echo '')"
    if [ -n "$pid" ] && kill -0 "$pid" 2>/dev/null; then
      log "netbird daemon already running (pid $pid)"
      return 0
    fi
    rm -f "$DAEMON_PIDFILE"
  fi

  if pgrep -f "$BIN_PATH service run" >/dev/null 2>&1; then
    log "netbird daemon already running"
    pgrep -f "$BIN_PATH service run" | head -n 1 > "$DAEMON_PIDFILE"
    return 0
  fi

  log "starting the netbird daemon without systemd (log: $DAEMON_LOG)"
  mkdir -p "$(dirname "$DAEMON_LOG")"
  rm -f "$DAEMON_SOCKET"
  nohup "$BIN_PATH" service run >>"$DAEMON_LOG" 2>&1 &
  echo $! > "$DAEMON_PIDFILE"
  note_change
}

ensure_daemon() {
  if daemon_responding; then
    log "netbird daemon is responding"
    return 0
  fi

  if has_systemd; then
    start_daemon_systemd
  else
    warn "systemd is not PID 1; supervising the daemon directly"
    warn "it will not survive a restart of this machine — re-run this script on boot"
    start_daemon_supervised
  fi

  wait_for_daemon || die "the netbird daemon did not become ready; see $DAEMON_LOG"
  log "netbird daemon is ready"
}

# ------------------------------------------------------------------ enrolment

is_connected() {
  local out
  out="$("$BIN_PATH" status 2>/dev/null)" || return 1
  printf '%s' "$out" | grep -q 'Management: Connected' \
    && printf '%s' "$out" | grep -q 'Signal: Connected'
}

# Enrolment is complete only when the config holds a peer private key and the
# daemon has stopped asking to log in. The daemon can write a config before
# enrolment succeeds, so the file alone is not proof.
peer_enrolled() {
  [ -s "${CONFIG_DIR}/config.json" ] || return 1
  grep -q '"PrivateKey"[[:space:]]*:[[:space:]]*"[^"]\+"' "${CONFIG_DIR}/config.json" || return 1
  ! "$BIN_PATH" status 2>/dev/null | grep -q 'NeedsLogin'
}

connect_peer() {
  if is_connected; then
    log "peer already connected to $MANAGEMENT_URL; leaving it alone"
    return 0
  fi

  local args=(up --management-url "$MANAGEMENT_URL")
  if [ -n "$NB_HOSTNAME" ]; then
    args+=(--hostname "$NB_HOSTNAME")
  fi
  if [ "$ALLOW_SERVER_SSH" = true ]; then
    args+=(--allow-server-ssh)
  fi

  # An already-enrolled peer that is merely down reconnects from stored config,
  # so a setup key is only required for first enrolment.
  if peer_enrolled; then
    log "existing peer configuration found; reconnecting"
    "$BIN_PATH" "${args[@]}" || die "netbird up failed; see $DAEMON_LOG"
  else
    [ -n "$SETUP_KEY" ] || die "no setup key: pass --setup-key-file PATH or set NETBIRD_SETUP_KEY"
    log "enrolling this peer with a setup key"
    # Prefer --setup-key-file where the client supports it, so the key never
    # appears in the process list.
    if "$BIN_PATH" up --help 2>&1 | grep -q -- '--setup-key-file'; then
      TMPDIR_SELF="${TMPDIR_SELF:-$(mktemp -d)}"
      local keyfile="$TMPDIR_SELF/setup.key"
      ( umask 077; printf '%s' "$SETUP_KEY" > "$keyfile" )
      "$BIN_PATH" "${args[@]}" --setup-key-file "$keyfile" || die "netbird up failed; see $DAEMON_LOG"
    else
      "$BIN_PATH" "${args[@]}" --setup-key "$SETUP_KEY" || die "netbird up failed; see $DAEMON_LOG"
    fi
  fi
  note_change

  local i
  for i in $(seq 1 30); do
    is_connected && { log "peer connected"; return 0; }
    sleep 1
  done
  warn "the peer did not report a full connection within 30s; current status follows"
  "$BIN_PATH" status || true
  return 1
}

print_status() {
  echo
  if [ -x "$BIN_PATH" ]; then
    "$BIN_PATH" status 2>&1 || true
  else
    echo "netbird is not installed"
  fi
}

main() {
  parse_args "$@"

  if [ "$STATUS_ONLY" = true ]; then
    print_status
    exit 0
  fi

  require_root
  resolve_setup_key

  if [ "$INSTALL_METHOD" = auto ]; then
    if command -v apt-get >/dev/null 2>&1; then INSTALL_METHOD=apt; else INSTALL_METHOD=binary; fi
    log "install method: $INSTALL_METHOD"
  fi
  # A pinned version is only selectable from release tarballs.
  if [ "$INSTALL_METHOD" = apt ] && [ "$WANTED_VERSION" != latest ]; then
    log "version pinning requires the binary method; switching to binary"
    INSTALL_METHOD=binary
  fi

  # Fail before touching the system if enrolment cannot possibly succeed.
  if [ "$SKIP_CONNECT" != true ] && [ -z "$SETUP_KEY" ] && [ ! -s "${CONFIG_DIR}/config.json" ]; then
    die "no setup key and no existing peer configuration: pass --setup-key-file PATH, set NETBIRD_SETUP_KEY, or use --skip-connect"
  fi

  ensure_prereqs
  ensure_tun

  case "$INSTALL_METHOD" in
    apt)    install_via_apt;    record_state apt ;;
    binary) install_via_binary; record_state bin ;;
  esac

  ensure_daemon

  if [ "$SKIP_CONNECT" = true ]; then
    log "--skip-connect set; not enrolling this peer"
  else
    connect_peer
  fi

  if [ "$CHANGED" = true ]; then
    log "done — configuration changed"
  else
    log "done — already in the desired state, nothing changed"
  fi
  print_status
}

main "$@"
