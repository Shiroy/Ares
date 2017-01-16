# Ares

[![Build Status](https://travis-ci.org/Shiroy/Ares.svg?branch=master)](https://travis-ci.org/Shiroy/Ares)

## Prepare

Packages needed on Ubuntu:

SFML
```
libsfml-dev
```

Protobuf
```
libprotobuf-dev
protobuf-compiler
```

## Compile
- mkdir install
- mkdir build
- cd build
- cmake -DCMAKE_INSTALL_PREFIX=../install ..
- make install
- cd ..

## Check code
Get Google cpplint:
- pip install cpplint

Check:
- cpplint --recursive client engine server shared
