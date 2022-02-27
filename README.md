# Client-Server

This is a very simple client-server application with ZeroMQ communication in between. The client side, which is written in C++, reads one line at a time from a .txt file. Each line contains randomly ordered integers seperated by spaces. Clients sends each line to server side in a request-reply pattern by implementing Lazy Pirate pattern (https://zguide.zeromq.org/docs/chapter4/). Server side, which is written in Python, sorts the integers in the recieved line returns the result to the client. Finally, the client writes these lines to a .txt file as they are recieved. 

## Dependencies for Running Locally
* cmake >= 3.11.3
  * [click here for installation instructions](https://cmake.org/install/)
* libzmq >= 4.3.5
  * libzmq source code or binary packages can be found [here](https://github.com/zeromq/libzmq)
* cppzmq >= 4.8.1
  * cppzmq is a C++ binding for libzmq which can be found [here](https://github.com/zeromq/cppzmq)
* pyzmq >= 22.3.0
  * pyzmq is python binding for ZeroMq which can be found [here](https://github.com/zeromq/pyzmq)
* numpy >= 1.22.2
  * numpy an be found [here](https://github.com/numpy/numpy)
* Python >= 3.7
* C++ compiler supporting c++17

## Basic Build Instructions for Client
1. Clone this repo.
2. Make a build directory in the client directory: `mkdir build && cd build`
3. Build: 
  * Linux: `cmake .. && make`
  * Winows: `cmake ..` produces .sln file in build directory which can be used to build the executable 

## Running for Generating and Checking .txt Files
The client executable will be placed in Client/bin directory which can be run from command line as follows:
```
client  -i "path_to_input_file.txt" -o "path_to_output_file.txt" -a "ip_adress_of_server" -p "port_number"
```

Python script for the server is in Server directory which can be run from command line as follows:
```
python server.py [port_number]
```

## Tools for Generating and Checking .txt Files
Python script for generating an input file is in Tools directory which can be run from command line as follows:
```
python inputGenerator.py [fileName] [maxLines] [maxIntsInLine] [maxInt]
```

Python script for checking if an output file is sorted is in Tools directory which can be run from command line as follows:
```
python outputChecker.py [fileName]
```
