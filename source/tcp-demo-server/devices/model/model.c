/*
*
* WORK IN PROGRESS!!
* 
*/

#include <stdio.h>
#include <pb_decode.h>
#include <pb_encode.h>
#include <protocol.h> 
#include <time.h>

#include "keyword_spotter.h"
#include "model.h"

typedef struct {
    int dummy;
} model_t;

static bool model_write_payload(pb_ostream_t* stream, const pb_field_t* field, void* const* arg) 
{
    UNUSED(stream);
    UNUSED(field);
    UNUSED(arg);

    return true;
}

static void model_poll(
    protocol_t* protocol,
    int device,
    pb_ostream_t* ostream,
    void* arg)
{
    UNUSED(protocol);
    UNUSED(device);
    UNUSED(ostream);
    UNUSED(arg);

    //if(have_prediction)
    UNUSED(model_write_payload);
    // protocol_send_data_chunk(protocol, device, 0, 1, ostream, model_write_payload);
} 

static void model_start(protocol_t* protocol, int device, void* arg)
{
    UNUSED(protocol);
    UNUSED(device);
    UNUSED(arg);

    IMAI_init();

    printf("MODEL START\n");

}

static void model_stop(protocol_t* protocol, int device, void* arg)
{
    UNUSED(protocol);
    UNUSED(device);
    UNUSED(arg);

    IMAI_init();

    printf("MODEL STOP\n");
}

static bool model_data_received(protocol_t* protocol, protocol_DataChunk* msg, pb_istream_t* stream, void* arg)
{
    UNUSED(protocol);
    UNUSED(arg);

   /* IMAI_DATA_IN_TYPE data[IMAI_DATA_IN_COUNT];
    for (int i = 0; i < msg->frame_count; i++) {

    }*/

    printf("-----------RECEIVED DATA--------------\n");
    printf("device: %d\n", msg->device);
    printf("stream: %d\n", msg->stream);
    printf("frame_count: %d\n", msg->frame_count);
    printf("total bytes: %ld\n", stream->bytes_left);

    uint8_t data[stream->bytes_left];
    if (!pb_read(stream, data, stream->bytes_left))
        return false;
   
    // Process the data here

    return true;
}

void model_register(protocol_t* protocol)
{
    model_t* state = (model_t*)malloc(sizeof(model_t));

    device_manager_t manager = {
        arg: state,
        configure_streams: NULL,
        start : model_start,
        stop : model_stop,
        poll : model_poll,
        data_received: model_data_received,
    };

    int model = protocol_add_device(
        protocol,
        protocol_DeviceType_DEVICE_TYPE_MODEL,
        "Model",
        "Example model test",
        manager);
    
    int in_stream = protocol_add_stream(
        protocol,
        model,
        "Audio In",
        protocol_StreamDirection_STREAM_DIRECTION_INPUT,
        protocol_DataType_DATA_TYPE_F32,
        0,
        100,
        NULL);
    protocol_add_stream_rank(protocol, model, in_stream, "Mono", IMAI_DATA_IN_COUNT, NULL);

    int out_stream = protocol_add_stream(
        protocol,
        model,
        "Predictions",
        protocol_StreamDirection_STREAM_DIRECTION_OUTPUT,
        protocol_DataType_DATA_TYPE_F32,
        0,
        100,
        NULL);
    protocol_add_stream_rank(protocol, model, out_stream, "Classes", IMAI_DATA_OUT_COUNT, (const char* []) IMAI_SYMBOL_MAP);

}
