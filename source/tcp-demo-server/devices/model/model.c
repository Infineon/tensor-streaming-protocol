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

// Structure to hold the state of the model
typedef struct {
    int input_stream_id;         // ID of the input stream
    int output_stream_id;        // ID of the output stream
    bool have_pending_inquire;   // Flag to indicate if there is a pending inquire
    IMAI_DATAOUT_TYPE tx_data[IMAI_DATAOUT_COUNT]; // Buffer to hold data to be transmitted
} model_t;

// Function to write the payload of the model's data to the output stream
static bool model_write_payload(
    protocol_t* protocol,
    int device_id,
    int stream_id,
    int frame_count,
    int total_bytes,
    pb_ostream_t* ostream,
    void* arg)
{
    UNUSED(protocol);
    UNUSED(device_id);
    UNUSED(stream_id);
    UNUSED(frame_count);

    model_t* model = (model_t*)arg;

    // Write the data from the model's tx_data buffer to the output stream
    if (!pb_write(ostream, (pb_byte_t*)model->tx_data, total_bytes))
        return false;

    return true;
}

// Function to poll the model and process any pending data
static void model_poll(
    protocol_t* protocol,
    int device,
    pb_ostream_t* ostream,
    void* arg)
{
    model_t* model = (model_t*)arg;

    // Continuously dequeue data from the model and send it as a data chunk
    for (bool continue_dequeue = true; continue_dequeue;)
    {
        switch (IMAI_dequeue(model->tx_data)) {
        case IPWIN_RET_SUCCESS:
            // Successfully dequeued data, send it as a data chunk
            protocol_send_data_chunk(protocol, device, model->output_stream_id, 1, 0, ostream, model_write_payload);
            break;
        case IPWIN_RET_NODATA:
            // No more data to dequeue
            continue_dequeue = false;
            break;
        case IPWIN_RET_ERROR:
        case IPWIN_RET_STREAMEND:
        default:
            // An error occurred, send an error message
            protocol_send_error_message(PROTOCOL_STATUS_UNSPECIFIED_ERROR, "Model dequeue failed", ostream);
            printf("MODEL: Model dequeue failed\n");
            continue_dequeue = false;
            break;
        }
    }

    // If there is no pending inquire, send a new data inquire request
    if (!model->have_pending_inquire) {
        int request_frames = IMAI_enqueue_batch_max_frames();
        if (request_frames > 0) {
            model->have_pending_inquire = true;
            protocol_send_data_inquire(protocol, device, model->input_stream_id, request_frames, ostream);
        }
    }
}

// Function to start the model
static void model_start(protocol_t* protocol, int device, pb_ostream_t* ostream, void* arg)
{
    model_t* model = (model_t*)arg;
   
    // Initialize the model
    if (IMAI_init() != IPWIN_RET_SUCCESS) {
        protocol_send_error_message(PROTOCOL_STATUS_UNSPECIFIED_ERROR, "Model initialization failed", ostream);
        printf("MODEL: Model initialization failed\n");
        return;
    }

    // Set the device status to active
    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_ACTIVE, "Model active");
    printf("MODEL: Started\n");

    // Send an initial data inquire request
    int request_frames = IMAI_enqueue_batch_max_frames();
    if (request_frames > 0) {
        model->have_pending_inquire = true;
        protocol_send_data_inquire(protocol, device, model->input_stream_id, request_frames, ostream);
    }
}

// Function to stop the model
static void model_stop(protocol_t* protocol, int device, pb_ostream_t* ostream, void* arg)
{
    UNUSED(arg);
    UNUSED(ostream);

    // Finalize the model
    IMAI_finalize();
  
    // Set the device status to ready
    protocol_set_device_status(protocol, device, protocol_DeviceStatus_DEVICE_STATUS_READY, "Model stopped");
    printf("MODEL: Stopped\n");
}

// Function to handle data received by the model
static bool model_data_received(protocol_t* protocol, protocol_DataChunk* msg, pb_istream_t* stream, void* arg)
{
    UNUSED(protocol);

    model_t* model = (model_t*)arg;
    UNUSED(model);

    // Read the data frames from the input stream and enqueue them to the model
    for (int i = 0; i < msg->frame_count; i++) {
        IMAI_DATAIN_TYPE data[IMAI_DATAIN_COUNT];
        if (!pb_read(stream, (pb_byte_t*)data, sizeof(data))) {
            printf("MODEL: Receive failed\n");
            return false;
        }

        if (IMAI_enqueue((IMAI_DATAIN_TYPE*)data) != IMAI_RET_SUCCESS) {
            protocol_set_device_status(protocol, msg->device, protocol_DeviceStatus_DEVICE_STATUS_ERROR, "Model enqueue failed");
            printf("MODEL: Model enqueue failed\n");
            return false;
        }
    }

    model->have_pending_inquire = false;

    return true;
}

// Function to register the model with the protocol
void model_register(protocol_t* protocol)
{
    // Allocate memory for the model state
    model_t* model = (model_t*)malloc(sizeof(model_t));
    memset(model, 0, sizeof(model_t));

    // Define the device manager for the model
    device_manager_t manager = {
        .arg = model,
        .configure_streams = NULL,
        .start = model_start,
        .stop = model_stop,
        .poll = model_poll,
        .data_received = model_data_received,
    };

    // Add the model device to the protocol
    int device = protocol_add_device(
        protocol,
        protocol_DeviceType_DEVICE_TYPE_MODEL,
        "Model",
        "Example model test",
        manager);

    // Add the input stream for the model
    int in_stream = protocol_add_stream(
        protocol,
        device,
        "Audio In",
        protocol_StreamDirection_STREAM_DIRECTION_INPUT,
        protocol_DataType_DATA_TYPE_F32,
        16000, // Sample rate
        -1,    // 1 channel
        NULL);
    protocol_add_stream_rank(protocol, device, in_stream, "Input", IMAI_DATAIN_COUNT, NULL);
    model->input_stream_id = in_stream;

    // Add the output stream for the model
    int out_stream = protocol_add_stream(
        protocol,
        device,
        "Predictions",
        protocol_StreamDirection_STREAM_DIRECTION_OUTPUT,
        protocol_DataType_DATA_TYPE_F32,
        14.285714285714286, // Sample rate
        1,                  // 1 channel
        NULL);
    model->output_stream_id = out_stream;
    protocol_add_stream_rank(protocol, device, out_stream, "Labels", IMAI_DATAOUT_COUNT, (const char* []) IMAI_SYMBOL_MAP);
}
