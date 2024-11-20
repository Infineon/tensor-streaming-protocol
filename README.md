# Tensor Streaming Protocol

This protocol defines a streaming mechanism used for communication between a client and a board. The protocol is intended to work over TCP, UDP, serial port, and Bluetooth.

One board may have one or more devices, and each device can have multiple input/output data streams. For example:

- Sensors typically have one output stream.
- Models have at least one input and one output stream.
- Playback devices may only have an input stream.

The protocol is based on [protobuf3](https://protobuf.dev/programming-guides/proto3/) and specified in two files:

- [model.proto](source/protocol/model.proto) - The base model that the request and response messages work against.
- [protocol.proto](source/protocol/protocol.proto) - The wire request and response messages.

On top of the protobuf, a helper API is defined in [protocol.h](source/protocol/protocol.h) using [Nanopb - Protocol Buffers for Embedded Systems](https://github.com/nanopb/nanopb).

## In this repo

```
└── source
    ├── DotNetCli               - CLI tool written in DotNet
    ├── protocol                - The actual protocol
    ├── python-example-client   - Example client written in python 
    └── tcp-demo-server         - TCP demo implementation of the protocol
```

## Terminology 

- **Board**: A board with one or more devices.
- **Device**: A device on a board (e.g., sensor, playback device, model).
- **Client**: Connects to a board via TCP, UDP, serial port, or Bluetooth.
- **Stream**: Each client can have multiple streams, either Input (to device) or Output (from device). Streams send Frames.
- **Frame**: A tensor with a specific shape sent periodically over a Stream.
- **Tensor**: A multidimensional array. Its dimensions are called the Rank.
- **Shape**: Sizes of all dimensions. For example, `[640, 480, 3]` is the shape of a video Frame.

## Protocol Session Example

1. **<= BoardCapabilitiesRequest**

   - The client sends a `BoardCapabilitiesRequest` message to inquire about the device capabilities.

2. **=>BoardCapabilitiesResponse**

   - The device responds with a `BoardCapabilitiesResponse` message detailing the available devices.
   - If `BoardCapabilitiesResponse.watchdog_timeout` is defined (>0), the client must send a `WatchdogResetRequest` at specified intervals (in milliseconds) to prevent the device from resetting itself.

3. **<=WatchdogResetRequest**

   - Resets the watchdog timer on the device. This request should be sent repeatedly every `watchdog_timeout` milliseconds.

For each device of interest:

4. **<= DeviceConfigurationRequest**

   - Configures the specified device. This request may not initialize the device but will prompt a response with a `DeviceConfigurationResponse` message that defines the expected data when a subscription is started.

5. **=> DeviceConfigurationResponse**

   - Describes the data streams (input/output) of the device once a subscription is started.

6. **<= StartRequest**

   - Initiates data streaming for the specified device. This request may also initialize the device if the firmware has not done so already.

7. **=> DataChunk**

   - For each subscription, the device streams data in `DataChunk` messages.

## tcp-demo-server

This is a demo TCP server implementation of the protocol that runs on Windows or Linux.

### How to Build and Run

On Ubuntu Linux:

1. **Install protobuf-compiler** (if not already installed):
    ```sh
    sudo apt install protobuf-compiler
    ```

2. **Download nanopb**: This will download nanopb into `source/nanopb`.
    ```sh
    cd source
    git clone https://github.com/nanopb/nanopb.git
    ```

3. **Build and run demo server**:
    ```sh
    cd source/tcp-demo-server
    make all
    ./main
    ```

Now continue with the DotNetCli client.

## DotNetCli

DotNetCli is a test client that can connect over TCP or Serial port.

![DotNetCli Screenshot](/images/Screenshot_DotNetCli.png)

### How to Build and Run

On Ubuntu Linux:

1. **Install .NET SDK required for the DotNetCli test app**:
    ```sh
    sudo apt-get install dotnet-sdk-9.0
    ```

2. **Start the client CLI**:
    ```sh
    cd source/DotNetCli
    dotnet run
    ```

## python-example-client

See [README.md](source/python-example-client) in source/python-example-client