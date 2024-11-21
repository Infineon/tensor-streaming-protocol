# Tensor Streaming Protocol

This protocol defines a streaming mechanism used for communication between a client and a board. The protocol is intended to work over TCP, UDP, serial port, and Bluetooth communication.
This protocol is designed to handle multiple data streams from sensors, models, and playback devices, enabling efficient data transfer and processing in embedded systems.

One board may have one or more devices, and each device can have multiple input/output data streams. For example:

- Sensors typically have one output stream.
- Models have at least one input and one output stream.
- Playback devices may only have an input stream.

The protocol is based on [protobuf3](https://protobuf.dev/programming-guides/proto3/) and specified in two files:

- [model.proto](source/protocol/model.proto) - Defines the base model for the messages used in the protocol.
- [protocol.proto](source/protocol/protocol.proto) - Specifies the wire format for request and response messages.

On top of the protobuf, a helper API is defined in [protocol.h](source/protocol/protocol.h) using [Nanopb - Protocol Buffers for Embedded Systems](https://github.com/nanopb/nanopb).

## In this repo

```
└── source
    ├── DotNetCli               - CLI tool written in DotNet for testing
    ├── protocol                - Protocol definition files and API helpers
    ├── python-example-client   - Example client written in python 
    └── tcp-demo-server         - TCP demo implementation of the protocol
```


### tcp-demo-server

This is a demo TCP server implementation of the protocol that runs on Windows or Linux.

#### How to Build and Run

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

For building and running on Windows, follow the instructions in the `source/tcp-demo-server` directory.

### DotNetCli

DotNetCli is a test client that can connect over TCP or Serial port.

![DotNetCli Screenshot](/images/Screenshot_DotNetCli.png)

#### How to Build and Run

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

### python-example-client

See [README.md](source/python-example-client) in source/python-example-client

## Terminology 

- **Board**: A hardware platform containing one or more devices.
- **Device**: A component on a board (e.g., sensor, playback device, model) that can produce or consume data.
- **Client**: An application that connects to a board via TCP, UDP, serial port, or Bluetooth to interact with devices.
- **Stream**: A data channel that can either send data (Output) or receive data (Input). Streams are associated with devices.
- **Frame**: A unit of data sent periodically over a stream, in the form of a tensor.
- **Tensor**: A multidimensional array used to represent data. The number of dimensions are referred to as rank.
- **Shape**: The size of each dimension in a tensor. For example, `[640, 480, 3]` represents the shape of a video frame.

## Protocol Session Example

The following steps outline a typical session between a client and a board using the Tensor Streaming Protocol:

1. **<= BoardCapabilitiesRequest**

    - The client sends a `BoardCapabilitiesRequest` message to inquire about the device capabilities on the board.

2. **=> BoardCapabilitiesResponse**

   - The board responds with a `BoardCapabilitiesResponse` message detailing the available devices and their capabilities.
   - If the response includes a `watchdog_timeout`, the client must periodically send `WatchdogResetRequest` messages to prevent the board from resetting.
   
3. **<= WatchdogResetRequest**

   - Resets the watchdog timer on the board. This request should be sent at intervals specified by `watchdog_timeout`.
   
For each device of interest:

4. **<= DeviceConfigurationRequest**

   - Configures the specified device with the desired options. This request prompts a `DeviceConfigurationResponse` from the board.

5. **=> DeviceConfigurationResponse**

   - The board responds with a `DeviceConfigurationResponse` message describing the configured data streams and their properties.

6. **<= StartRequest**

    - The client sends a `StartRequest` to initiate data streaming for the specified device.

7. **=> DataChunk**

    - The board streams data in `DataChunk` messages for each active subscription.

## Instructions for Registering a Device to the Protocol (Example)

This guide provides an example on how to register a device using the Protocol API. Specifically, 
it focuses on defining and using the essential callback functions: `configure_streams`, `start`, `stop`, and `poll`.

By following this guide, you can successfully register a device using the Protocol API, configure its streams, and handle its data using the provided callback functions. The example provided demonstrates how to register a microphone sensor, but the same principles can be applied to other sensors as well. For details on creating a protocol instance and tying it to a serial port, TCP socket, or Bluetooth, refer to [PROTOCOL_BOARD_SETUP.md](PROTOCOL_BOARD_SETUP.md).

For a complete firmware example, see [mtb-example-imagimob-streaming-protocol](https://XXXX)

### Step-by-Step Guide

#### 1. Implement the Device Registration Function

Combine all steps into a single function that registers your device. This function initializes the device-specific data structure, sets up the device manager, registers the device with the protocol, and adds relevant options.

##### Example Device Registration Function
```c
#include "protocol.h"

typedef struct {
    int16_t audio_buffer0[FRAME_SIZE];
    int16_t audio_buffer1[FRAME_SIZE];
    int16_t* active_rx_buffer;
    int16_t* full_rx_buffer;
    bool pdm_pcm_initialized;
    cyhal_pdm_pcm_t pdm_pcm;
    bool have_data;
    bool stereo;
    int skipped_frames;
} mic_device_t;

static bool mic_configure_streams(protocol_t* protocol, int device, void* arg);
static void mic_start(protocol_t* protocol, int device, void* arg);
static void mic_stop(protocol_t* protocol, int device, void* arg);
static void mic_poll(protocol_t* protocol, int device, pb_ostream_t* ostream, void* arg);
static bool mic_write_payload(protocol_t* protocol, int device_id, int stream_id, int frame_count, int total_bytes, pb_ostream_t* ostream, void* arg);

#define MIC_OPTION_KEY_GAIN 1
#define MIC_OPTION_KEY_STEREO 2
#define MIC_OPTION_KEY_FREQUENCY 3

bool mic_register(protocol_t* protocol) {
    int status;

    // Allocate memory for the device-specific data structure
    // Static memory may be used if a no malloc policy exists
    mic_device_t* mic = (mic_device_t*)malloc(sizeof(mic_device_t));
    if (mic == NULL)
        return false;
    memset(mic, 0, sizeof(mic_device_t));

    // Set up the device manager with the callbacks
    device_manager_t manager = {
        .arg = mic,
        .configure_streams = mic_configure_streams,
        .start = mic_start,
        .stop = mic_stop,
        .poll = mic_poll,
        .data_received = NULL // has no input streams
    };

    // Register the device with the protocol
    int device = protocol_add_device(
        protocol,
        protocol_DeviceType_DEVICE_TYPE_SENSOR,
        "Microphone",
        "PCM Microphone",
        manager);

    if (device < 0)
        return false;

    // Add integer option for gain
    status = protocol_add_option_int(
        protocol,
        device,
        MIC_OPTION_KEY_GAIN,
        "Gain",
        "Microphone gain in dB",
        0, -20, 20);

    if (status != PROTOCOL_STATUS_SUCCESS)
        return false;

    // Add boolean option for stereo mode
    status = protocol_add_option_bool(
        protocol,
        device,
        MIC_OPTION_KEY_STEREO,
        "Stereo",
        "Stereo or Mono",
        false);

    if (status != PROTOCOL_STATUS_SUCCESS)
        return false;

    // Add oneof option for frequency
    status = protocol_add_option_oneof(
        protocol,
        device,
        MIC_OPTION_KEY_FREQUENCY,
        "Frequency",
        "Sample frequency (Hz)",
        1,
        (const char*[]) { "8 kHz", "16 kHz" },
        2);

    if (status != PROTOCOL_STATUS_SUCCESS)
        return false;

    if (!mic_configure_streams(protocol, device, manager.arg))
        return false;

    return true;
}

```

#### 2. Define the configure_streams Callback

The configure_streams callback is invoked every time a DeviceConfigurationRequest is received. This callback is responsible for configuring the data streams for the device, including setting the stream's frequency, direction, data type, and tensor shape. After the callback is executed, a DeviceConfigurationResponse is sent.

##### Example configure_streams Callback

```c
static bool mic_configure_streams(protocol_t* protocol, int device, void* arg) {
    UNUSED(arg);

    int frequency_index;
    int frequency;

    // Get the frequency option value
    if (protocol_get_option_oneof(protocol, device, MIC_OPTION_KEY_FREQUENCY, &frequency_index) != PROTOCOL_STATUS_SUCCESS) {
        protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ERROR, "Mic: Failed to get option frequency.");
        return true; // Keep the connection open to allow for reconfiguration
    }

    // Determine the frequency based on the option index
    switch (frequency_index) {
        case 0:
            frequency = SAMPLE_RATE_8_KHZ;
            break;
        case 1:
            frequency = SAMPLE_RATE_16_KHZ;
            break;
        default:
            protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ERROR, "Mic: Invalid frequency index.");
            return true;
    }

    // Get the stereo option value
    bool stereo;    
    if (protocol_get_option_bool(protocol, device, MIC_OPTION_KEY_STEREO, &stereo) != PROTOCOL_STATUS_SUCCESS) {
        protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ERROR, "Mic: Failed to get option stereo.");
        return true;
    }

    // Clear any existing streams for the device
    if (protocol_clear_streams(protocol, device) != PROTOCOL_STATUS_SUCCESS) {
        protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ERROR, "Mic: Failed to clear streams.");
        return true;
    }

    // Determine the maximum number of frames in a chunk based on stereo option
    int max_number_of_frames_in_chunk = stereo ? FRAME_SIZE / 2 : FRAME_SIZE;
    
    // Add a new stream for audio data
    int stream = protocol_add_stream(
        protocol,
        device,
        "Audio",
        protocol_StreamDirection_STREAM_DIRECTION_OUTPUT,
        protocol_DataType_DATA_TYPE_S16,
        frequency,
        max_number_of_frames_in_chunk,
        NULL);

    if (stream < 0) {
        protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ERROR, "Mic: Failed to add streams.");
        return true;
    }

    // Add tensor rank based on stereo option
    if (stereo) {
        protocol_add_stream_rank(protocol, device, stream, "Channel", 2, (const char*[]) {"Left", "Right"});
    } else {
        protocol_add_stream_rank(protocol, device, stream, "Channel", 1, (const char*[]) {"Mono (Left)"});
    }

    // Set device status to ready after successful configuration
    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_READY, "Microphone is ready.");

    return true;
}

```

#### 3. Define the start and stop Callbacks

The `start` callback is invoked when a `StartRequest` is received, and it initializes and starts the device. The `stop` callback is invoked when a `StopRequest` is received, and it stops and de-initializes the device. These functions manage the device's active state.

##### Example start Callback

```c
static void mic_start(protocol_t* protocol, int device, void* arg) {
    cy_rslt_t result;
    int gain_db;
    int frequency_index;
    int sample_rate;
    bool stereo;
    mic_device_t* mic = (mic_device_t*)arg;

    // Get the configured options for frequency, stereo, and gain
    protocol_get_option_oneof(protocol, device, MIC_OPTION_KEY_FREQUENCY, &frequency_index);
    protocol_get_option_bool(protocol, device, MIC_OPTION_KEY_STEREO, &stereo);
    protocol_get_option_int(protocol, device, MIC_OPTION_KEY_GAIN, &gain_db);

    // Determine the sample rate based on the frequency index
    switch (frequency_index) {
        case 0:
            sample_rate = SAMPLE_RATE_8_KHZ;
            break;
        case 1:
        default:
            sample_rate = SAMPLE_RATE_16_KHZ;
            break;
    }

    printf("MIC START STREAMING sample_rate=%d stereo=%d gain_db=%d\r\n", sample_rate, stereo, gain_db);

    // Initialize and start the hardware
    result = pcm_start(mic, sample_rate, gain_db, stereo ? CYHAL_PDM_PCM_MODE_STEREO : CYHAL_PDM_PCM_MODE_LEFT);
    if (CY_RSLT_SUCCESS != result) {
        protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ERROR, "Mic: Failed to initialize hardware.");
        return;
    }

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ACTIVE, "Device is streaming");
}
```

##### Example stop Callback

```c
static void mic_stop(protocol_t* protocol, int device, void* arg) {
    cy_rslt_t result;
    mic_device_t* mic = (mic_device_t*)arg;

    printf("MIC STOP STREAMING\r\n");

    // Stop and de-initialize the hardware
    result = pcm_stop(mic);
    if (CY_RSLT_SUCCESS != result) {
        protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ERROR, "Mic: Failed to stop the PDM/PCM operation.");
        return;
    }

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_READY, "Device stopped");
}

```

#### 4. Define the poll Callback

When a device is in the `Active` state, the poll callback is called periodically to check if there is data available and send it using the `protocol_send_data_chunk` function. The `protocol_send_data_chunk` function will send a `DataChunk` message.

##### Example poll Callback

```c
static void mic_poll(protocol_t* protocol, int device, pb_ostream_t* ostream, void* arg) {
    mic_device_t* mic = (mic_device_t*)arg;

    if (mic->have_data) {
        int frames_in_chunk = mic->stereo ? FRAME_SIZE / 2 : FRAME_SIZE;

        // Send a DataChunk message with the available data
        protocol_send_data_chunk(protocol, device, 0, frames_in_chunk, mic->skipped_frames, ostream, mic_write_payload);
        mic->skipped_frames = 0;
    }
}
````

#### Define the mic_write_payload Helper Function

The `mic_write_payload` function is used by `protocol_send_data_chunk` to write the actual data to the output stream.

##### Example mic_write_payload Function

```c
static bool mic_write_payload(protocol_t* protocol, int device_id, int stream_id, int frame_count, int total_bytes, pb_ostream_t* ostream, void* arg) {
    UNUSED(protocol);
    UNUSED(stream_id);
    UNUSED(frame_count);

    mic_device_t* mic = (mic_device_t*)arg;

    // Write the payload data to the output stream
    if (!pb_write(ostream, (const pb_byte_t*)mic->active_rx_buffer, total_bytes))
        return false;

    mic->have_data = false;

    return true;
}

```

## License

[MIT License](LICENSE.md)

## Contact

support@imagimob.com