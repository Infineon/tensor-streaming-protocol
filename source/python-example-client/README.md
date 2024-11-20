# Python Example Client for Tensor Streaming Protocol

This project is a Python example client that communicates with a serial device using the Tensor Streaming Protocol. It can send configuration requests, start data streaming, and process incoming data chunks.

## Features

- Send configuration requests to the device
- Start and stop data streaming
- Parse and display incoming data chunks as numpy arrays

## Requirements

- Python 3.6+
- pyserial
- numpy
- protobuf
- grpcio-tools

## Installation

### Using `setup.py`

You can install the package and its dependencies using the `setup.py` file. Run the following command:

```sh
pip install .
```

### Using requirements.txt

Alternatively, you can install the dependencies using the requirements.txt file. Run the following command:

```sh
pip install -r requirements.txt
```

### Generating Protocol Buffer Files

The project uses Protocol Buffers for efficient serialization and deserialization of data. The files are provided but you can regenerate them using the provided custom build command.

Run the following command to generate the Protocol Buffer files:

```sh
python setup.py build_proto
```

## Usage

After installing the package, you can run the client to communicate with the serial device. Make sure to adjust the SERIAL_PORT and BAUD_RATE constants in the script to match your setup.

### Running the Client

```sh
python main.py
```