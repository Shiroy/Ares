# Ares

[![Build Status](https://travis-ci.org/Shiroy/Ares.svg?branch=master)](https://travis-ci.org/Shiroy/Ares)

## Prepare

Get the `sfml` latest version.

## Compile

For compiling files you can try the following instructions:

Generate CMake scripts:
```
cmake -DCMAKE_BUILD_TYPE=Debug -DCMAKE_INSTALL_PREFIX:PATH=./ -G "CodeBlocks - Unix Makefiles" .
```

Compile Client and Server and install assets:
```
cmake --build ./cmake-build-debug --target install_Ares -- -j 4
```

## CLion tips

As CLion is build on CMake, you can open the project by 
simply opening the top-level CMakeLists.txt file in the 
project root directory. 

It will generate the scripts for you in `cmake-build-debug`.
Then, you just have to run the script named install_Ares.
Finally run the server and the client.

## Run
### Server

Run server the client will obviously connect:
```
cmake-build-debug/server/ares_server
```

### Client

Run client
```
cmake-build-debug/client/ares_client
```

