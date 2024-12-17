from setuptools import setup, find_packages, Command
from grpc_tools import protoc
import os

class CustomBuildCommand(Command):
    """Custom build command to generate protobuf files."""
    description = 'Generate protobuf files from .proto files'
    user_options = []

    def initialize_options(self):
        pass

    def finalize_options(self):
        pass

    def run(self):
        proto_path = os.path.join(os.path.dirname(__file__), '..', 'protocol')  # Adjust your proto path here

        # Run protoc commands to generate Python files from .proto files
        protoc.main([
            'grpc_tools.protoc',
            f'--proto_path={proto_path}',
            '--python_out=.',
            '--grpc_python_out=.',
            os.path.join(proto_path, 'model.proto')
        ])
        protoc.main([
            'grpc_tools.protoc',
            f'--proto_path={proto_path}',
            '--python_out=.',
            '--grpc_python_out=.',
            os.path.join(proto_path, 'protocol.proto')
        ])

setup(
    name='python-example-client',
    version='0.1',
    packages=find_packages(),
    cmdclass={
        'build_proto': CustomBuildCommand,
    },
    install_requires=[
        'pyserial',
        'numpy',
        'protobuf',
        'grpcio-tools'
    ],
    entry_points={
        'console_scripts': [
            'python-example-client=your_module_name:main',  # Adjust the module and main function
        ],
    },
    author='Imagimob AB',
    author_email='albert.seward@imagimob.com',
    description='A Python example client for Tensor Streaming Protocol',
    long_description=open('README.md').read(),
    long_description_content_type='text/markdown',
    url='https://bitbucket.org/imagimob/tensor-streaming-protocol',
    classifiers=[
        'Programming Language :: Python :: 3',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
    ],
    python_requires='>=3.6',
)
