"""
Tensor Streaming Protocol Client

This script communicates with a serial device using the Tensor Streaming Protocol.
It sends configuration requests, starts data streaming, and processes incoming data chunks.

Dependencies:
- protocol_pb2
- model_pb2
- pyserial
- numpy

Make sure to have the required protobuf files compiled and available in the same directory.

"""

import protocol_pb2
import model_pb2
from google.protobuf.internal.decoder import _DecodeVarint32
from google.protobuf.internal.encoder import _EncodeVarint
import serial
import serial.tools.list_ports
import numpy as np

# Constants
SERIAL_PORT = 'COM5'
BAUD_RATE = 115200

def encode_varint(value):
    """Encodes a value as a varint"""
    data = []
    _EncodeVarint(data.append, value)
    return b''.join(data)

def decode_varint(buffer):
    """Decodes a varint from the buffer"""
    (value, pos) = _DecodeVarint32(buffer, 0)
    return (value, pos)

def send_message(serial_port, message):
    """Sends a message over the serial port"""
    data = message.SerializeToString()
    size = len(data)
    serial_port.write(encode_varint(size))
    serial_port.write(data)
    serial_port.flush()  # Ensure all data is sent
    print(f'Sent message: {message}')

def receive_message(serial_port):
    """Receives a message from the serial port"""
    size_data = bytearray()
    
    # Read the size of the incoming message
    while True:
        byte = serial_port.read(1)
        if not byte:
            return None
        size_data.extend(byte)
        try:
            size, pos = decode_varint(size_data)
            if pos == len(size_data):
                break
        except IndexError:
            continue  # Read more bytes for the varint
    
    # Read the actual data
    data = bytearray()
    while len(data) < size:
        packet = serial_port.read(size - len(data))
        if not packet:
            return None
        data.extend(packet)

    return bytes(data)

def parse_payload(payload, frame_count, stream_config):
    """Parses the payload into a numpy array based on the shape and datatype"""
    dtype_map = {
        model_pb2.DATA_TYPE_U8: np.uint8,
        model_pb2.DATA_TYPE_S8: np.int8,
        model_pb2.DATA_TYPE_U16: np.uint16,
        model_pb2.DATA_TYPE_S16: np.int16,
        model_pb2.DATA_TYPE_U32: np.uint32,
        model_pb2.DATA_TYPE_S32: np.int32,
        model_pb2.DATA_TYPE_F32: np.float32,
        model_pb2.DATA_TYPE_F64: np.float64,
    }
    
    if stream_config.datatype not in dtype_map:
        raise ValueError(f"Unsupported data type: {stream_config.datatype}")
    
    # Fetch shape from stream configuration
    shape = [dim.size for dim in stream_config.shape]

    # Add "batch" to shape. This may vary from chunk to chunk
    shape.insert(0, frame_count) 

    dtype = dtype_map[stream_config.datatype]
    array = np.frombuffer(payload, dtype=dtype)
    array = array.reshape(shape)
    return array

def main():
    # List available serial ports to check the correct port
    ports = list(serial.tools.list_ports.comports())
    if not ports:
        print("No serial ports found.")
        return

    for port in ports:
        print(f"Detected port: {port.device} - {port.description}")

    # Configure the serial port (ensure correct port mapping)
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
    except serial.SerialException as e:
        print(f"Failed to connect to the serial port: {e}")
        return

    # Send a BoardCapabilitiesRequest message
    request = protocol_pb2.Request()
    request.capabilities.device = -1
    send_message(ser, request)

    # Send a DeviceConfigurationRequest
    request = protocol_pb2.Request()
    request.config.device = 0
    
    # Set option 20 to true.
    # We assume that device 0 is a microphone and option 20 is stereo/mono
    option = request.config.options.add()
    option.option_id = 20
    option.bool_value = True
    send_message(ser, request)

    # Send a StartRequest message
    request = protocol_pb2.Request()
    request.start.device = 0
    send_message(ser, request)    

    # Stop after a given number of data chunks
    chunks_to_receive = 10

    device_configurations = {}
    while chunks_to_receive > 0:
        try:
            # Listen for responses and print them
            response_data = receive_message(ser)
            
            if response_data:
                response = protocol_pb2.Response()
                
                try:
                    response.ParseFromString(response_data)
                except Exception as e:
                    print(f"Error parsing message with type 'protocol.Response': {e}")
                    continue
                
                if response.HasField('config'):
                    config = response.config
                    print(f"Received Device Configuration Response for device {config.device}:")
                    device_configurations[config.device] = config

                elif response.HasField('data'):
                    data_chunk = response.data
                    print("Received Data Chunk:")
                    
                    # Get the shape and datatype for the stream
                    if data_chunk.device in device_configurations:
                        device_config = device_configurations[data_chunk.device]
                        stream_config = device_config.streams[data_chunk.stream]
                        array = parse_payload(data_chunk.payload, data_chunk.frame_count, stream_config)
                        print(f"Device: {data_chunk.device} Stream: {data_chunk.stream} Numpy array:", array)
                        chunks_to_receive -= 1
                    else:
                        print(f"Device configuration for device {data_chunk.device} not found.")
                                     
                elif response.HasField('capabilities'):
                    capabilities = response.capabilities
                    print("Received Board Capabilities Response:")
                    print(capabilities)
                    
                elif response.HasField('error'):
                    error = response.error
                    print("Received Error Response:")
                    print(error)
                    
                else:
                    print("Received unknown message type.")
            else:
                print("No data received. Waiting...")

        except KeyboardInterrupt:
            break
        except Exception as e:
            print(f"An error occurred: {e}")

    # Send a StopRequest message
    request = protocol_pb2.Request()
    request.stop.device = -1
    send_message(ser, request)

if __name__ == '__main__':
    main()
