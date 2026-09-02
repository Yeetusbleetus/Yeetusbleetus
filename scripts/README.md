# install-netbird.sh

Idempotent installer and enrolment for the [NetBird](https://netbird.io) client
on Debian/Ubuntu hosts, containers and micro-VMs. It follows the
[official Linux install](https://docs.netbird.io/get-started/install/linux) and
adds the two things that guide leaves out: safe re-runs, and a daemon that
starts where systemd is not PID 1.

## Quick start

```bash
sudo NETBIRD_SETUP_KEY='<setup-key>' ./scripts/install-netbird.sh
```

Preferred, so the key never reaches the process list or shell history:

```bash
sudo ./scripts/install-netbird.sh --setup-key-file /run/secrets/netbird_key
```

Self-hosted management server:

```bash
sudo ./scripts/install-netbird.sh \
  --setup-key-file /run/secrets/netbird_key \
  --management-url https://netbird.example.com:443
```

Run `./scripts/install-netbird.sh --help` for every flag, and `--status` to
report the current state without changing anything.

## What idempotent means here

Each run converges on the desired state and reports whether anything changed.

| Step | Skipped when |
|---|---|
| apt repository setup | keyring and the exact source line are already in place |
| package or binary install | the wanted version is already installed |
| daemon start | the daemon already answers on its socket |
| enrolment | the peer already reports Management and Signal connected |

A second run of a converged host makes no network calls to package
repositories, touches no files, and exits 0 with "nothing changed". The
upstream one-liner instead aborts with "NetBird seems to be installed already".

## Install methods

`--method auto` (the default) uses the apt repository when `apt-get` is
present and falls back to the release tarball. `--method binary` downloads from
GitHub releases and verifies the published SHA-256 checksum before installing.
Pinning `--version vX.Y.Z` forces the binary method, since apt only carries the
current release.

The latest version is resolved from `pkgs.netbird.io`, then the GitHub API, then
the `releases/latest/download` redirect, which needs neither an API quota nor a
token.

## Running without systemd

`netbird service install` registers a systemd unit, which fails in containers
and micro-VMs where PID 1 is something else. When systemd is not PID 1 the
script starts `netbird service run` under `nohup`, records the PID in
`/run/netbird-daemon.pid`, and logs to `/var/log/netbird/daemon.log`. A re-run
reuses that process instead of starting a second copy.

That daemon does not survive a reboot. Re-run the script from your container
entrypoint or an init hook.

## Requirements

- Root, and `/dev/net/tun`. In Docker: `--cap-add NET_ADMIN --device /dev/net/tun`.
- Outbound access to `pkgs.netbird.io` and `github.com` to install, and to your
  management, signal and relay servers to connect. NetBird prefers UDP for peer
  traffic, so an HTTP-proxy-only egress path is not enough to bring tunnels up.
