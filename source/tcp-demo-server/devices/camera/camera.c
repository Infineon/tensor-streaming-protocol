#include <stdio.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <protocol.h> 
#include <time.h>

#include "camera.h"

#define CAMERA_OPTION_KEY_EXPOSURE 10
#define CAMERA_OPTION_KEY_RESOLUTION 20
#define CAMERA_OPTION_KEY_COLOR 30

typedef struct _foobar_camera {
    clock_t period;
    clock_t dummy_throttle;
} foobar_camera_t;

static bool camera_write_payload(
    protocol_t* protocol,
    int device_id,
    int stream_id,
    int frame_count,
    int total_bytes,
    pb_ostream_t* ostream,
    void* arg)
{
    foobar_camera_t* state = (foobar_camera_t*)arg;
    UNUSED(state);
    UNUSED(protocol);
    UNUSED(device_id);
    UNUSED(stream_id);
    UNUSED(frame_count);

    int write_buffer = 100;
    uint8_t data[write_buffer];
    for (int j = 0; j < total_bytes; j += write_buffer) {

        int write_count = j + write_buffer > total_bytes ? total_bytes - j : write_buffer;

        for (int i = 0; i < write_count; i++) {
            data[i] = 42;
        }

        if (!pb_write(ostream, data, write_count))
            return false;
    }
    return true;
}

static void camera_poll(
    protocol_t* protocol, 
    int device, 
    pb_ostream_t* ostream,
    void* arg) 
{
    foobar_camera_t* state = (foobar_camera_t*)arg;
    clock_t time = clock();

    // Dummy throttle to emulate data frequency
    if ((time - state->dummy_throttle) < state->period)
         return;
    state->dummy_throttle = time;

    protocol_send_data_chunk(protocol, device, 0, 1, 0, ostream, camera_write_payload);
}

static void camera_start(protocol_t* protocol, int device, void* arg)
{
    foobar_camera_t* state = (foobar_camera_t*)arg;
    UNUSED(state);

    printf("CAMERA START STREAMING\n");

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ACTIVE, "Device is streaming");

}

static void camera_stop(protocol_t* protocol, int device, void* arg)
{
    foobar_camera_t* state = (foobar_camera_t*)arg;
    UNUSED(state);

    printf("CAMERA STOP STREAMING\n");

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_READY, "Device stopped");
}

static bool camera_configure_streams(protocol_t* protocol, int device, void* arg)
{
    foobar_camera_t* state = (foobar_camera_t*)arg;

    int resolution;
    int width;
    int height;
    float fps;
    protocol_get_option_oneof(protocol, device, CAMERA_OPTION_KEY_RESOLUTION, &resolution);

    switch (resolution) {
    case 0:
        width = 320;
        height = 200;
        fps = 30;
        break;
    case 1:
        width = 640;
        height = 480;
        fps = 30;
        break;
    case 2:
        width = 1024;
        height = 768;
        fps = 30;
        break;
    default:
        return false;
    }

    bool color;
    protocol_get_option_bool(protocol, device, CAMERA_OPTION_KEY_COLOR, &color);

    protocol_clear_streams(protocol, device);
    int max_numer_of_frames_in_chunk = 1;
    int stream = protocol_add_stream(
        protocol,
        device, 
        "Video",
        protocol_StreamDirection_STREAM_DIRECTION_OUTPUT,
        protocol_DataType_DATA_TYPE_U8, 
        fps,
        max_numer_of_frames_in_chunk,
        NULL);

    protocol_add_stream_rank(protocol, device, stream, "Width", width, NULL);
    protocol_add_stream_rank(protocol, device, stream, "Height", height, NULL);

    if (color) {
        protocol_add_stream_rank(
            protocol,
            device,
            stream, 
            "Color", 
            3, 
            (const char* []) { "Red", "Green", "Blue" });
    }

    state->dummy_throttle = clock();
    state->period = 10000 / fps;

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_READY, "Camera is ready.");

    return true;
}

void camera_register(protocol_t* protocol) 
{   
    foobar_camera_t* state = (foobar_camera_t*)malloc(sizeof(foobar_camera_t));

    device_manager_t manager = {
        arg: state,
        configure_streams: camera_configure_streams,
        start: camera_start,
        stop: camera_stop,
        poll: camera_poll,
        data_received: NULL, // has no input streams
    };

    int camera = protocol_add_device(
        protocol, 
        protocol_DeviceType_DEVICE_TYPE_SENSOR,
        "Camera", 
        "Example camera sensor",
        manager);

    protocol_add_option_float(
        protocol,
        camera, 
        CAMERA_OPTION_KEY_EXPOSURE,
        "Exposure",
        "Whiteness level",
        50.0, 0.0, 100.0);

    protocol_add_option_oneof(
        protocol, 
        camera, 
        CAMERA_OPTION_KEY_RESOLUTION, 
        "Resolution", 
        "Camera resolution", 
        1,
        (const char* []) { "320x200 30fps", "640x480 30fps", "1024x768 30fps" }, 
        3);

    protocol_add_option_bool(
        protocol,
        camera, 
        CAMERA_OPTION_KEY_COLOR,
        "Color", 
        "Color or B/W",
        false);

    camera_configure_streams(protocol, camera, state);
}
