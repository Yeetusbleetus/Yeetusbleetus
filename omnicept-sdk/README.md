# omnicept-sdk

An independent C++17 client library for the **HP Omnicept Runtime** (the service behind the HP Reverb G2 Omnicept Edition's eye tracking, heart rate, PPG, IMU, cognitive load and face camera).

It follows the public API described in HP's C++ reference (`HP::Omnicept::Glia`, `Client`, `Abi::*` domain types), and talks to the runtime over ZeroMQ using protobuf schemas recovered from the runtime itself.

> **Status: untested against real hardware.** The library builds cleanly and passes its test suite against a bundled **mock** runtime. Several wire-protocol details are inferred or guessed (see [Protocol assumptions](#protocol-assumptions)), so expect to adjust `ProtocolConfig` the first time you run it against the real HP Omnicept Runtime.

## Where things come from

| Part | Source | Confidence |
|---|---|---|
| Public API: class names, methods, fields, enums, `Client` state/result semantics | HP's C++ reference page | Documented |
| Message schemas (`proto/*.proto`, 28 files) | Rebuilt from protobuf descriptors embedded in the HP Omnicept Runtime 1.14 binaries; they compile with `protoc` | Recovered |
| Numeric `MessageType` ids | Id/name table in the runtime binary; agrees with the order of the documented `MessageType` enum | Recovered |
| Default endpoint `tcp://localhost:13352` | The port constant recurs throughout runtime and client binaries | Inferred |
| Handshake flow and framing | `SessionControlSignal` states, two PAIR data sockets per client | Partly inferred, partly guessed |

## Build

Requirements: CMake ≥ 3.16, a C++17 compiler, Protobuf, ZeroMQ (libzmq) and cppzmq.

**Linux**

```sh
sudo apt install cmake g++ protobuf-compiler libprotobuf-dev libzmq3-dev cppzmq-dev
cmake -S . -B build
cmake --build build -j
./build/omnicept_tests        # runs against the mock runtime
```

**Windows** (where the runtime actually lives), with [vcpkg](https://vcpkg.io):

```bat
vcpkg install protobuf zeromq cppzmq --triplet x64-windows
cmake -S . -B build -DCMAKE_TOOLCHAIN_FILE=%VCPKG_ROOT%/scripts/buildsystems/vcpkg.cmake
cmake --build build --config Release
```

## Usage

```cpp
#include "omnicept/Glia.h"
using namespace HP::Omnicept;

auto license = std::make_unique<Abi::SessionLicense>(
    "<clientId>", "<accessKey>", Abi::LicensingModel::REV_SHARE, /*isRunningInEditor=*/false);
// or: std::make_unique<Abi::SessionLicense>(Abi::SessionLicense::Core())

auto builder = Glia::StartBuildClient_Async(
    "my-app", std::move(license),
    Abi::SubscriptionList::ForTypes({Abi::MessageType::heartRate, Abi::MessageType::eyeTracking}),
    [](Client::State s) { /* PAUSED / RUNNING / DISCONNECTED */ });

auto client = builder.getBuildClientResultOrThrow();  // throws HandshakeError, TransportError, ...

client->registerCallback<Abi::HeartRate>([](std::shared_ptr<Abi::HeartRate> hr) {
    std::cout << hr->rate << " bpm\n";
});
client->startClient();                                  // clients start PAUSED
auto latest = client->getLastData<Abi::EyeTracking>();  // last-value cache
client->disconnectClient();
```

`examples/heart_rate_monitor.cpp` is a complete program:

```sh
heart_rate_monitor --clientId <id> --accessKey <key> --license revshare
```

### Receivable types

`HeartRate`, `HeartRateFrame`, `HeartRateVariability`, `EyeTracking`, `EyeTrackingFrame`, `CognitiveLoad`, `CognitiveLoadInputFeature`, `PPG`, `PPGFrame`, `IMU`, `IMUFrame`, `SceneColor`, `SceneColorFrame`, `CameraImage`, `VSync`, `ByteMessage`, `DataVaultResult`.

`EyePupillometry` is declared for API compatibility, but no schema for it was found in the runtime, so it is never decoded.

## Licensing

The SDK forwards your `clientId`/`accessKey` and requested licensing model to the runtime unchanged, and the runtime decides what you receive. Subscriptions your license doesn't cover are reported through `setSubscriptionResultCallback` (for example `NOT_LICENSED_ERROR` or `REJECTED_BY_USER_ERROR`), and those messages are never sent. Only a Core license can be requested without credentials. The SDK checks this before connecting.

## Protocol assumptions

Every unconfirmed detail is a field in `include/omnicept/ProtocolConfig.h`, so none of it is hard-coded:

| Setting | Default | Basis |
|---|---|---|
| `host`, `port` | `localhost`, `13352` | inferred |
| `handshakeSocketType` | `DEALER` | **guess** (try `PAIR` or `REQ` if the handshake times out) |
| Handshake | send `CONNECT` (license, handshake versions, ABI version). On `ACCEPT`, connect the returned data endpoints and send `CLIENT_READY`. Done on `FINALIZE`; `REJECT` raises `HandshakeError` | inferred from the `SessionControlSignal` enum |
| `sendOnEndpointInUri` | `true` | **guess** about which returned URI is the client→runtime direction |
| `handshakeVersions`, `endpointAbiVersion` | `{1}`, empty | **guess** (the runtime rejects mismatches by name, so its error should say what it expects) |
| `messageVersion` | `0` | **guess** |
| `multipartFraming` | `true`: frame 0 is the `PackageDeclaration` header, frame 1 is the body | **guess**, consistent with the documented header/body split in `IMessage` |
| Connection id format | `<name>_<uuid>` | **guess** (in `Connection.cpp`) |

If connecting to the real runtime fails, the error message and the runtime's log (`%ProgramData%\HP\HP Omnicept\`) are the best guides. A `TransportError` saying there was "no response" means the endpoint or socket type is wrong. A `HandshakeError` with a reason means the runtime understood the request and is telling you what it disliked.

## Differences from HP's SDK

- `Glia::StartBuildClient_Async(clientName, license, subscriptions, stateCallback, config)`: the reference page doesn't list `Glia`'s factory function, so this signature is this library's own.
- Extras: `Glia::BuildClient` (synchronous), `ProtocolConfig`, `SubscriptionList::ForTypes` / `GetSubscriptionListToAll`, `Client::setSubscriptionResultCallback`, `Client::getConnectionId`, `SessionLicense::Core()`.
- Not implemented: `ConnectionIdentifier`, `Dependency`/`DependencyList`, `TimestampCalculator`, `IMessage`, `BackpackColors`/`Battery` messages, sending `ByteMessage`s.

## Layout

```
include/omnicept/   public headers (Glia.h, Client.h, ProtocolConfig.h, abi/*)
src/                implementation: Codec (domain <-> protobuf), Connection (sockets + handshake)
proto/              recovered wire schemas
tests/              MockRuntime + end-to-end tests
examples/           heart_rate_monitor
```

This project is not affiliated with or endorsed by HP Inc. "HP" and "Omnicept" are trademarks of HP Inc.
