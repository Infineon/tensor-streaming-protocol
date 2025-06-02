/******************************************************************************
* File Name:   protocol_example.c
*
* Description: This file shows how to interact with our dummy_driver using the
*              protocol. It may be used as a template for various devices.
*              The only function that is called from the top level is the 
*              dev_register(protocol_t* protocol) function.
*
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdbool.h>

#include "clock.h"
#include "protocol/protocol.h"
#include "protocol/pb_encode.h"
#include "protocol_example.h"
#include "dummy_driver.h"


/******************************************************************************
 * Macros
 *****************************************************************************/
#define OPTION_SCALE_VALUE          1
#define OPTION_SCALE                2
#define OPTION_WAVEFORM             3

/******************************************************************************
 * Global Variables
 *****************************************************************************/
// Typically you are using some struct to keep track of the device's internal state if needed.
// For the example we need to assume some data to send periodically.
// This should be calculated. Assume for example 8000 samples per second and a waveform frequency 
// of 100 Hz. Then there is about 80 samples per period.
typedef struct {
    bool running;
    int16_t buffer[80]; // Keep space for 80 samples in the local buffer.
    int stream_id;
    
    // Keep track of our options.
    int waveform;
    int scale;
    bool apply_scale;
    
} device_t;

device_t dev;

/*******************************************************************************
* Function Prototypes
*******************************************************************************/

// Local functions that can be used for support. 
// Not mandatory.
static bool _init_hw(device_t* dev);
static bool _device_start(device_t* dev );
static bool _device_stop(device_t* dev );

/* Protocol callback's
** These are mandatory functions. The actual contents may vary  
** but some have a typical response function. Since they are 
** callback's their names can be changed if desired.
*/
static bool _write_payload( protocol_t* protocol, int device_id, int stream_id, int frame_count,
                            int total_bytes, pb_ostream_t* ostream, void* arg);
                            
static bool _configure_streams(protocol_t* protocol, int device_id, void* arg);
static void _start_streams(protocol_t* protocol, int device_id, pb_ostream_t* ostream, void* arg);
static void _stop_streams(protocol_t* protocol, int device_id, pb_ostream_t* ostream, void* arg);
static void _poll_streams(protocol_t* protocol, int device_id, pb_ostream_t* ostream, void* arg);

/*******************************************************************************
* Function Definitions
*******************************************************************************/

/******************************************************************************
* Function Name: _init_hw
********************************************************************************
* Summary:
*   Initializes the Hardware
*
* Parameters:
*   dev: Pointer to device handle.
*
* Return:
*   True if operation is successful, otherwise false.
*
* Note: This is only a placeholder for possible initialization of hardware.
*       It is up to the needs and requirements of the driver.
*
*******************************************************************************/
static bool _init_hw(device_t* dev)
{
    
    UNUSED(dev);
    bool fail = false;
    
    if ( fail )
    {
        return false;
    }

    printf("dummy device initialized.\n");
    return true;
}

/*******************************************************************************
* Function Name: _device_start
********************************************************************************
* Summary: _device_start can hold local code that is needed for starting any
*          device. It is up to the design if and how this is used. 
*
* Parameters:
*           device* dev: A pointer to a handle. 

* Return:
*     true if successful.
*
*******************************************************************************/
static bool _device_start(device_t* dev )
{
    dev->running = true;
    reset_dummy_driver();
    printf("dummy device started.\n");
    return true;
}

/*******************************************************************************
* Function Name: _device_stop
********************************************************************************
* Summary:
*    A function used to de-initialize and stop the device if needed. 
*
* Parameters:
*       device* dev: A pointer to a handle. 
*
* Return:
*     true if successful.
*
*******************************************************************************/
static bool _device_stop(device_t* dev)
{
    dev->running = false;
    printf("dummy device stopped.\n");
    return true;
}

/*******************************************************************************
* Function Name: _configure_streams
********************************************************************************
* Summary:
*   Called when the device is configured or re-configured by DEEPCRAFT Studio.
*
* Parameters:
*   protocol: Pointer the protocol handle
*   device: The device index
*   arg: Pointer the device struct. 
*
* Return:
*   True to keep the connection open, otherwise false.
*
* Note: 
*   This is called automatically when Studio first finds the device and
*   when the configuration is changed from within Studio. The protocol supports
*   several channels in the same stream as well as multidimensional data.
*
*******************************************************************************/
static bool _configure_streams(protocol_t* protocol, int device_id, void* arg)
{
    
	/*******************************************************************************
	**  A device can have multiple streams of data and each stream can have a
	**  multidimensional array of data. A typical example of having multiple
	**  streams if when you have multiple sensors in the same physical device
	**  for example an IMU containing an accelerometer and a gyro.
	**
	**  This example only configures one stream with one dimensional data.
	*******************************************************************************/

    device_t* dev = (device_t*)arg;

    if (protocol_clear_streams(protocol, device_id) != PROTOCOL_STATUS_SUCCESS) {
        protocol_set_device_status(
                protocol,
                device_id,
                protocol_DeviceStatus_DEVICE_STATUS_ERROR,
                "Failed to clear streams.");
        return true;
    }

	/*******************************************************************************
	**  A stream is transmiting frames (samples) over the protocol grouped in chunks.
	**  Sending multiple frames together is a good way of reducing protocol overhead.
	**  In this example we decided to put 80 frames in each chunk.
	**  We also decided that our dummy driver will generate 8000 frames (samples) per second.
	**  For audio this would be equal of one audio channel (mono) sampled at 8000Hz.
	*******************************************************************************/
    int max_numer_of_frames_in_chunk = 80; // Configure this for frames a 80 samples.
                                                                                 
    int stream = protocol_add_stream(
        protocol,
        device_id,
        "Wave", // The name of the stream.
        protocol_StreamDirection_STREAM_DIRECTION_OUTPUT, // This device stream is outputting data (typical for a sensor)
        protocol_DataType_DATA_TYPE_S16,
        8000, // Number of frames per second (frequency).
        max_numer_of_frames_in_chunk,
        "Samples"); // This is typically the physical unit or type of value being sent. 

    if (stream < 0) {
        protocol_set_device_status(
                protocol,
                device_id,
                protocol_DeviceStatus_DEVICE_STATUS_ERROR,
                "Failed to add streams.");
        return true;
    }

    dev->stream_id = stream;

	/*******************************************************************************
	**  A stream can be thought of as a tensor or array with one or multiple dimensions.
	**  With each dimension we need to associate a name and a length. We can also pass in
	**  an optional array of string pointers to name each element index of the dimension.
	**
	**  A simple wave, as in our example, have a single dimension of length 1 (a scalar).
	**  Since it only has one dimension we call protocol_add_stream_rank once.
	**  We chose to name this dimension "Primary axis". Since it only has one index,
	**  we don't care to name it.
	*******************************************************************************/
    protocol_add_stream_rank(
        protocol,
        device_id,
        stream,
        "Primary axis",
        1,   // A length of 1 means that each data point is a scalar.
        NULL // Array of string pointers. Gives names to the diffrent indexes. Or NULL if the indexes shouldn't be named.
    );



	/*******************************************************************************
	**  Below is an example of a multi-dimensional stream containing an 640x480 RGB (color) image.
	**  The image has three dimensions/ranks; height, width and channel (rgb).
	**
	**  The first stream rank added will become the first dimension.
	**  In this example we add width, height and channel so
	**  In C-code array this will be array[width][height][channel]
	*******************************************************************************/
    // protocol_add_stream_rank(
    //     protocol,
    //     device_id,
    //     stream,
    //     "width",
    //     640, // 640px width                     
    //     NULL // We pass NULL as we don't want to name the individual pixels...
    // );

    // protocol_add_stream_rank(
    //     protocol,
    //     device_id,
    //     stream,
    //     "height",
    //     480, // 480px height                     
    //     NULL // We pass NULL as we don't want to name the individual pixels...
    // );

    // protocol_add_stream_rank(
    //     protocol,
    //     device_id,
    //     stream,
    //     "channel",
    //     3,  // 3 color channels                
    //     (const char* []) { "r", "g", "b" } // Array of string pointers. Gives names to the diffrent indexes. 
    // );
        
	/*******************************************************************************
	** Below is another example, of a stream containing data from an IMU device
	** containing both an accelerometer and a  gyroscope.
	*******************************************************************************/
	// protocol_add_stream_rank(
    //     protocol,
    //     device_id,
    //     stream,
    //     "Accelerometer",
    //     3,                     
    //     (const char* []) { "Accel_X", "Accel_Y", "Accel_Z" } // Array of string pointers. Gives names to the diffrent indexes. 
    // );

    // protocol_add_stream_rank(
    //     protocol,
    //     device_id,
    //     stream,
    //     "Gyroscope",
    //     3,                     
    //     (const char* []) { "Gyro_X", "Gyro_Y", "Gyro_Z" } // Array of string pointers. Gives names to the diffrent indexes. 
    // );

    protocol_set_device_status(
            protocol,
            device_id,
            protocol_DeviceStatus_DEVICE_STATUS_READY,
            "Device is ready.");

    printf("Stream is configured!\n");

    return true;
}

/*******************************************************************************
* Function Name: _start_streams
********************************************************************************
* Summary:
*   Called by the protocol engine when streaming is started by Studio. 
*   This might be a good place to also initialize the device.
*
* Parameters:
*   protocol: Pointer the protocol handle
*   device: The device index
*   ostream: Pointer to the output stream to write to
*   arg: Pointer the device struct.
*
*******************************************************************************/
static void _start_streams(protocol_t* protocol, int device_id, pb_ostream_t* ostream, void* arg)
{
    int waveform;
    int scale;
    bool apply_scale;
    
    device_t* dev = (device_t*)arg;

    UNUSED(ostream);
    UNUSED(arg);
    
	/*******************************************************************************
	** Here when starting the device, we read out the user options for the device.
	** These options can be modified from the Studio UI. We store the latest options in
	** our struct that holds our device related information.
	*******************************************************************************/
    protocol_get_option_oneof(protocol, device_id, OPTION_WAVEFORM, &waveform);
    protocol_get_option_bool(protocol, device_id, OPTION_SCALE, &apply_scale);
    protocol_get_option_int(protocol, device_id, OPTION_SCALE_VALUE, &scale);

    dev->waveform = waveform;
    dev->scale = scale;
    dev->apply_scale = apply_scale;
    
    /** Optionally have a device specific start function. **/
    bool result = _device_start( dev );

    if (!result) {
        protocol_set_device_status( protocol, device_id, protocol_DeviceStatus_DEVICE_STATUS_ERROR, 
                                                         "Failed to start device.");
        printf("Starting the stream failed somehow!\n");
        return;
    }

    protocol_set_device_status(
            protocol,
            device_id,
            protocol_DeviceStatus_DEVICE_STATUS_ACTIVE,
            "Device is streaming");
}

/*******************************************************************************
* Function Name: _stop_streams
********************************************************************************
* Summary:
*  Called by the protocol engine when streaming is stopped by Studio.
*  This might be a good place to also stop/free up the device.
*
* Parameters:
*  protocol: Pointer the protocol handle
*  device_id: The device index
*  ostream: Pointer to the output stream to write to
*  arg: Pointer the device struct.
*
*******************************************************************************/
static void _stop_streams(protocol_t* protocol, int device_id, pb_ostream_t* ostream, void* arg)
{

    device_t* dev = (device_t*)arg;
    UNUSED(ostream);

    /** Optionally have a device specific stop function. **/
    bool result = _device_stop(dev);

    if ( !result ) {
        protocol_set_device_status( protocol, device_id, protocol_DeviceStatus_DEVICE_STATUS_ERROR,
                                                         "Failed to stop the device.");
        printf("Stopping the stream failed somehow!\n");                                                 
        return;
    }

    protocol_set_device_status(
            protocol,
            device_id,
            protocol_DeviceStatus_DEVICE_STATUS_READY,
            "Device stopped");
}

/*******************************************************************************
* Function Name: _poll_streams
********************************************************************************
* Summary:
*  Called periodically to send data messages.
*
* Parameters:
*  protocol: Pointer the protocol handle
*  device: The device index
*  ostream: Pointer to the output stream to write to
*  arg: Pointer the device struct.
*
*******************************************************************************/
static void _poll_streams(protocol_t* protocol, int device_id, pb_ostream_t* ostream, void* arg)
{
    
	/*******************************************************************************
	**  This callback is called by the protocol engine for each registered and started device.
	**  protocol_call_device_poll() in usbd.c triggers this call.
	**
	**  This will be the place where data is collected and passed on using the protocol.
	**  How it is collected is not part of this example since it can vary a lot
	**  between different devices. Some timer or flags may be needed to keep track
	**  of data and data rate.
	**
	**  For simplicity we have moved out the actual gathering of data to an external
	**  function. This returns a simple flag if data is available.
	**  We pass on the settings we got from the options earlier as separate values.
	*******************************************************************************/

    // Check if there is data available.
    device_t* dev = (device_t*)arg;
    bool have_data = fetch_dummy_driver_data( dev->waveform, dev->scale, dev->apply_scale, dev->buffer );

    // If data is available, write the protocol header to the outstream.
    if ( have_data ) {
        protocol_send_data_chunk(
            protocol,
            device_id,
            dev->stream_id,  // Stream ID. See configure streams. 
            80, // This chunk we are sending here will have 80 frames.
            0,  // Skipped frames, not used.
            ostream,
            _write_payload);    // How to write the actual payload.
    }
}

/*******************************************************************************
* Function Name: _write_payload
********************************************************************************
* Summary:
*  Used by protocol_send_data_chunk to write the actual data.
*
* Parameters:
*  protocol: Pointer the protocol handle
*  device_id: The device index
*  stream_id: The stream index
*  frame_count: Number of frames to write
*  total_bytes: Total number of bytes to write (= frame_count * sizeof(type) * frame_shape.flat)
*  ostream: Pointer to the output stream to write to
*  arg: Pointer the device struct.
*
* Return:
*   True if data writing is successful, otherwise false.
*
* Note:
*   This is a callback called after the protocol header previous sent away from
*   above. It sends the raw data collected into our buffer.
*******************************************************************************/
static bool _write_payload(
    protocol_t* protocol,
    int device_id,
    int stream_id,
    int frame_count,
    int total_bytes,
    pb_ostream_t* ostream,
    void* arg)
{
    UNUSED(protocol);
    UNUSED(stream_id);
    UNUSED(frame_count);
    UNUSED(device_id);

    // Just send away the raw data with the actual number of bytes precalculated for us.
    device_t* dev = (device_t*)arg;
    if (!pb_write(ostream, (const pb_byte_t *)dev->buffer, total_bytes))
    {
        return false;
    }

    return true;
}


/*******************************************************************************
* Function Name: dev_register
********************************************************************************
* Summary:
*   Registers this device. This is the only exported symbol from this object.
*
* Parameters:
*   protocol: Pointer the protocol handle
*
* Returns:
*   True if registration is successful, otherwise false.
*
* Notes:
*   This does not communicate with studio at this time. It only sets up the
*   structures for the protocol to be used. 
*
*   This registering of the device describes how the device will appear in
*   Studio. A board can have multiple devices.
*
*   From studio it will then be possible to select the options provided if any.
*
*******************************************************************************/
bool dev_register(protocol_t* protocol)
{

	/** Optionally doing an early hardware initialization here.  **/
    if(!_init_hw( (device_t*) &dev))
    {
        return false;
    }


	/*******************************************************************************
	**    When the Studio communicates over the protocol it uses a few callback's
	**    that is provided here. Configure, start, stop and poll.
	**    The poll function is called frequently to allow for the protocol to send
	**    data.
	*******************************************************************************/
    device_manager_t manager = {
        .arg = (void*)&dev,
        .configure_streams = _configure_streams,
        .start = _start_streams,
        .stop = _stop_streams,
        .poll = _poll_streams,
        .data_received = NULL /* has no input streams */
    };


    /** A board can have several devices. This adds it to the list of devices. **/
    int device_id = protocol_add_device(
        protocol,
        protocol_DeviceType_DEVICE_TYPE_SENSOR,
        "Toy device",
        "Description of the toy device",
        manager);

    if(device_id < 0)
    {
        return false;
    }


	/*******************************************************************************
	** A device can have several options that allow for various configurations.
	** This could be settings like framerate, amplitudes or anything.
	**
	** Options comes in various types. One is integer options where a value
	** can be sent from studio and used in what ever way it likes.
	**
	** In this example I call it scaling and it is later used for scale up the
	** dummy driver value with an integer.
	*******************************************************************************/
    int status = protocol_add_option_int(
        protocol,
        device_id,
        OPTION_SCALE_VALUE,
        "Scaling",
        "Multiplier for waveform.",
        2,          // Default
        0,10 );     // range

    if (status != PROTOCOL_STATUS_SUCCESS)
    {
        printf("Adding option int failed!\n");    
        return false;
    }


	/*******************************************************************************
	**  Boolean options can for example be to turn features on and of.
	**
	**  In this example I use it later for enabling or disabling scaling of the
	**  data from the dummy driver.
	*******************************************************************************/
    status = protocol_add_option_bool(
        protocol,
        device_id,
        OPTION_SCALE,
        "Multiply",
        "Description",
        false       // Default
        );

    if(status != PROTOCOL_STATUS_SUCCESS)
    {
        printf("Adding option bool failed\n");
        return false;
    }

	/*******************************************************************************
	**  One-of options is mutually exclusive options. The options will be seen
	**  in the Studio as a drop-down list.
	**
	**  In this example I use it to select from one of four different waveforms.
	*******************************************************************************/
    status = protocol_add_option_oneof(
        protocol,
        device_id,
        OPTION_WAVEFORM,
        "Waveform",
        "Which waveform to generate.",
        2,              // Default. Index 2 in this example is the square wave
        (const char* []) { "Sawtooth", "Triangle", "Square", "Sin(xt)" },
        4);

    if (status != PROTOCOL_STATUS_SUCCESS)
    {
        printf("Adding option one_of failed!\n");    
        return false;
    }

    return true;
}
