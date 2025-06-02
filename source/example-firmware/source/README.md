# About the code example

This code example is for demonstrating how to use protocol v2 for adding devices to DEEPCRAFT Studio.

The protocol itself is agnostic to the underlying hardware. What is needed is an output stream of data to a COM PORT for studio to find it.

This example has replaced any sensor devices with a hardware independent dummy driver. This is to be able to demonstrate and focus on the protocol. The example can be used as a template for real sensors by modifying and renaming some parameters. The hardware drivers also needs to be added and data be available for writing.

The protocol is based on protobuf which is a general protocol structure developed by Google. This document is not intended to describe protobuf itself or how the underlying binary protocol packets are designed. The focus is on how to add and use the protocol to stream data from any hardware device.

Most of what is needed is to configure some structs. Letting the protocol and manager knowing about what to expect.

THE BOARD

1.  First the protocol is created with a name, serial nummber, and a firmware version. This can be seen in the main() function. The return is a handle that is further used for adding devices and related actions.
 
2. Studio will later query every com port it finds with a command "GetCapabilities" and if it reponds and have a uuid serial number as a string it is accepted. Thus any board name can be used.

THE DEVICES

3.  Once the basic is created, devices needs to be added along with the option the device can accept. The dummy device is in this example is added in the protocol_example.c in the function dev_register( protocol_t* protocol ){ }

4. The manager struct holds some information on needed callbacks and a user pointer .arg. Needed callbacks are     
    .configure_streams
    .start
    .stop
    .poll
    
ADDING OPTIONS    

5. Following the creation of the device is adding of any option the Studio user may need. It could be data rates, data sizes, enabling features. It is up to the design to define what might be needed. This options comes in a few types.
 
oneof is the type where selections is mutually exclusive and it will show up in a dropdown list in Studio.
bool  is the type where single features can be turned on and off.
int   is if you like to provide a specific value to the device.

    At this point in code data is only registered internally on the board for the Studio to read once connected. Have a look at the function for more details about the parameters.
    

WHAT HAPPENS NEXT?    
Back to the main function:
    Once the device is registered internally the usb CDC (Communication Device Class) device is set up and the main goes into a loop for reading commands.
    
6.  Incoming data and polling. Since this protocol and many drivers are single threaded, the mechanism is that when the protocol tries to read a character the protocol polling is called. Reading will usually return nothing and it will continue trying. If the series of characters actually read make up a command, the command is processed before the next polling. This polling can be seen in the usbd.c file. Also note that all registered devices will be polled one by one. Having many devices with large data or heavy processing will have an impact on performance.

7. Since it is driven by polling, any device driver handling a sensor must use some communication to notify the polling that data is ready. Interrupts can be used for the device driver itself but not for sending data.

STREAMS
8.  Once the board is identified in Studio, Studio will send a command that will call the _configure_streams. In this function the appearance of the data will be defined. Data packages is identified by stream_id Adding ranks or dimensions is also done here. If multiple ranks are added they appear in c-style ordering from left to right as they are added. array[1st][2nd][3rd]  or a block of data[Y][X][Z] then Y should be the first rank to add. 

9. Using multiple streams can be useful in cases like audio. Right channel vs Left channel.
    If one prefer, this data can also be combined in ranks or as another multidimensional array.


10.  For new users of this protocol I would recommend spending some time building this example and look how it appears in studio. Experimenting with adding more options and possible read them out. Adding options is easily done by A. Define a macro for the option id. (Look at the top of the file). B. Copy an existing add_option_xxx function and rename, modify the parameters. Make sure you use the MACRO defined above as the identifier. The new option should the be seen in Studio.

11. Reading out the options is done via some functions.
    protocol_get_option_oneof(protocol, device_id, OPTION_ID_1, &variable);
    protocol_get_option_bool(protocol, device_id, OPTION_ID_2, &variable);
    protocol_get_option_int(protocol, device_id, OPTION_ID_3, &variable);

The device_id, OPTION_ID_ defines the device and what you request. The variable will get the actual value selected in the option list. The Option id is the same user defined value you had when you added the device.

12. If a model is generated and added the data to be enqueued is ready in the poll function. Protocol is not needed in such case.









