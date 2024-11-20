all: protocol_pb2.py model_pb2.py

requirements:
	pip install protobuf pyserial

protocol_pb2.py:
	protoc --python_out=. protocol.proto --proto_path=../protocol/

model_pb2.py:
	protoc --python_out=. model.proto --proto_path=../protocol/

clean:
	rm -f protocol_pb2.py model_pb2.py
