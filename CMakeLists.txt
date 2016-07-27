cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(Ares)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(protocol)
add_subdirectory(engine)
