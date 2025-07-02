Using the [Tensor Streaming Protocol](https://bitbucket.org/imagimob/tensor-streaming-protocol/src/master/), we have implemented this basic example firmware to stream data into DEEPCRAFT™ Studio. Drawing inspiration from our implementation, you can either implement your own firmware from scratch or extend the example firmware to collect data at different rates or add the support of additional sensors. 

To learn how to register sensors or boards to stream data into the DEEPCRAFT™ Studio using Tensor Streaming Protocol, follow this step-by-step tutorial. See [here](https://developer.imagimob.com/getting-started/tensor-streaming-protocol/registering-sensors-using-protocolv2).

Note: <br/>
1. You do not need to understand the protocol implementation in order to register and stream data to/from boards or devices in DEEPCRAFT™ Studio. You will interact with the protocol through the protocol functions and callbacks as shown in the tutorial and the source code in this repository. It is important to note that you should not modify the protocol or any files within the protocol folder. Modifications to the protocol folder should only be made by advanced users who wish to understand the implementation details of the protocol.
<br/>
2. The example-firmware is tested with the PSOC™6 AI Kit on ModusToolbox™ 3.4. This example firmware should work on any PSOC™6 board with serial or USB port. However, we have seen issues when using the debug port for serial communication.



