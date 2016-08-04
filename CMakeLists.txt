cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(Ares)

add_definitions(-std=c++11)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(shared)
add_subdirectory(engine)
add_subdirectory(vendor)

add_custom_target(install_${PROJECT_NAME}
        make install
        DEPENDS ares_client ares_engine ares_shared ares_server
        COMMENT "Installing ${PROJECT_NAME}")