#include <stdio.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <protocol.h>
#include <time.h>

#include "mic.h"

#define MIC_OPTION_KEY_GAIN 10
#define MIC_OPTION_KEY_STEREO 20
#define MIC_OPTION_KEY_FREQUENCY 30

typedef struct _foobar_mic {
    clock_t period;
    clock_t dummy_throttle;
} foobar_mic_t;

static void mic_start(protocol_t* protocol, int device, void* arg)
{
    foobar_mic_t* state = (foobar_mic_t*)arg;

    UNUSED(state);

    printf("MIC START STREAMING\n");

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ACTIVE, "Device is streaming");
}

static void mic_stop(protocol_t* protocol, int device, void* arg)
{
    foobar_mic_t* state = (foobar_mic_t*)arg;
    UNUSED(state);

    printf("MIC STOP STREAMING\n");

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_READY, "Device stopped");
}

static bool mic_write_payload(
    protocol_t* protocol,
    int device_id,
    int stream_id,
    int frame_count,
    int total_bytes,
    pb_ostream_t* ostream,
    void* arg) 
{
    foobar_mic_t* state = (foobar_mic_t*)arg;
    UNUSED(state);
    UNUSED(protocol);
    UNUSED(device_id);
    UNUSED(stream_id);
    UNUSED(frame_count);

    int total_elements = total_bytes / sizeof(float);

    int write_buffer = 100;
    float data[write_buffer];
    for (int j = 0; j < total_elements; j += write_buffer) {

        int write_count = j + write_buffer > total_elements ? total_elements - j : write_buffer;

        for (int i = 0; i < write_count; i++) {
            data[i] = i + 0.25;
        }

        if (!pb_write(ostream, (const pb_byte_t *)data, write_count * sizeof(float)))
            return false;
    }

    return true;
}

static void mic_poll(protocol_t* protocol, int device, pb_ostream_t* ostream, void* arg) 
{
    foobar_mic_t* state = (foobar_mic_t*)arg;
    
    clock_t time = clock();

    // Dummy throttle to emulate data frequency
    if ((time - state->dummy_throttle) < state->period)
        return;
    state->dummy_throttle = time;

    protocol_send_data_chunk(protocol, device, 0, 42, 0, ostream, mic_write_payload);
}

static bool mic_configure_streams(protocol_t* protocol, int device, void* arg)
{
    foobar_mic_t* state = (foobar_mic_t*)arg;
  
    int frequency_index;
    float frequency;
    protocol_get_option_oneof(protocol, device, MIC_OPTION_KEY_FREQUENCY, &frequency_index);

    switch(frequency_index) {
    case 0:
        frequency = 8000;
        break;
    case 1:
        frequency = 16000;
        break;
    case 2:
        frequency = 44100;
        break;
    default:
        return false;
    }

    bool stereo;
    protocol_get_option_bool(protocol, device, MIC_OPTION_KEY_STEREO, &stereo);

    int gain_db;
    protocol_get_option_int(protocol, device, MIC_OPTION_KEY_GAIN, &gain_db);

    protocol_clear_streams(protocol, device);
    int max_numer_of_frames_in_chunk = 160;
    int stream = protocol_add_stream(
        protocol,
        device, 
        "Audio", 
        protocol_StreamDirection_STREAM_DIRECTION_OUTPUT,
        protocol_DataType_DATA_TYPE_F32, 
        frequency, 
        max_numer_of_frames_in_chunk,
        NULL);

    state->dummy_throttle = clock();
    state->period = 42 * 10000 / frequency;  

    if (stereo) {
        protocol_add_stream_rank(protocol, device, stream, "Channel", 2, (const char* []) { "Left", "Right" });
    } else {
        protocol_add_stream_rank(protocol, device, stream, "Channel", 1, (const char* []) { "Mono" });
    }

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_READY, "Microphone is ready.");

    return true;
}

void mic_register(protocol_t* protocol) 
{
    foobar_mic_t* state = (foobar_mic_t*)malloc(sizeof(foobar_mic_t));

    device_manager_t manager = {
       arg: state,
       configure_streams: mic_configure_streams,
       start: mic_start,
       stop: mic_stop,
       poll: mic_poll,
       data_received : NULL, // has no input streams
    };

    int mic = protocol_add_device(
        protocol,
        protocol_DeviceType_DEVICE_TYPE_SENSOR,
        "Microphone", 
        "Example microphone", 
        manager);

    protocol_add_option_int(
        protocol,
        mic, 
        MIC_OPTION_KEY_GAIN, 
        "Gain",
        "Microphone gain in dB",
        0, -20, 20);

    protocol_add_option_bool(
        protocol, 
        mic, 
        MIC_OPTION_KEY_STEREO, 
        "Stereo", 
        "Stereo or Mono", 
        true);

    protocol_add_option_oneof(
        protocol, 
        mic,
        MIC_OPTION_KEY_FREQUENCY,
        "Frequency", 
        "Sample frequency (Hz)", 
        1, 
        (const char* []) { "8 kHz", "16 kHz", "44.1 kHz" }, 
        3);

    mic_configure_streams(protocol, mic, manager.arg);
}