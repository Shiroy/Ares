cmake_minimum_required(VERSION 3.0)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

project(Ares)

add_subdirectory(client)
add_subdirectory(server)
add_subdirectory(protocol)
add_subdirectory(engine)

add_custom_target(install_${PROJECT_NAME}
        make install
        DEPENDS ares_client ares_engine ares_protocol ares_server
        COMMENT "Installing ${PROJECT_NAME}")