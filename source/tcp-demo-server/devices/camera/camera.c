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
    int total_byte_size;
    clock_t period;
    clock_t dummy_throttle;
} foobar_camera_t;


static bool camera_write_payload(pb_ostream_t *stream, const pb_field_t *field, void * const *arg) {

    foobar_camera_t* state = (foobar_camera_t*)*arg;

    int total_size = state->total_byte_size;

    if (!pb_encode_tag_for_field(stream, field))
        return false;

    if (!pb_encode_varint(stream, total_size))
        return false;

    int write_buffer = 100;
    uint8_t data[write_buffer];
    for (int  j = 0; j < total_size; j+= write_buffer) {

        int writeCount = j + write_buffer > total_size ? total_size - j : write_buffer;

        for (int i = 0; i < writeCount; i++) {
            data[i] = 42;
        }

        if (!pb_write(stream, data, writeCount))
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

    protocol_send_data_chunk(protocol, device, 0, 1, ostream, camera_write_payload);
}

static void camera_start(protocol_t* protocol, int device, void* arg)
{
    foobar_camera_t* state = (foobar_camera_t*)arg;
    UNUSED(state);

    printf("CAMERA START STREAMING\n");

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_Active, "Device is streaming");

}

static void camera_stop(protocol_t* protocol, int device, void* arg)
{
    foobar_camera_t* state = (foobar_camera_t*)arg;
    UNUSED(state);

    printf("CAMERA STOP STREAMING\n");

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_Ready, "Device stopped");
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
        protocol_StreamDirection_OutputStream, 
        protocol_DataType_DATA_TYPE_U8, 
        fps,
        max_numer_of_frames_in_chunk,
        0,0,
        NULL);

    protocol_add_stream_rank(protocol, device, stream, "Width", width, NULL);
    protocol_add_stream_rank(protocol, device, stream, "Height", height, NULL);

    state->total_byte_size = width * height* max_numer_of_frames_in_chunk * protocol_get_datatype_size(protocol_DataType_DATA_TYPE_U8);
    if (color) {
        protocol_add_stream_rank(
            protocol,
            device,
            stream, 
            "Color", 
            3, 
            (const char* []) { "Red", "Green", "Blue" });
        state->total_byte_size *= 3;
    }

    state->dummy_throttle = clock();
    state->period = 10000 / fps;

    protocol_set_device_status(protocol, device, protocol_DeviceStatus_Ready, "Camera is ready.");

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
        protocol_DeviceType_Sensor, 
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
