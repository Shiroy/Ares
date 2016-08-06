set(source_client
        src/main.cpp
        src/Game.cpp src/Game.h
        src/PlayerCommands.cpp src/PlayerCommands.h
        src/NetworkThread.cpp src/NetworkThread.cpp)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR}) #To acces to protobuf generated files with #include <>
file(GLOB_RECURSE proto_files ../protocol/*.proto)
protobuf_generate_cpp(PROTO_SRC PROTO_HDR ${proto_files})

include_directories(${SFML_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/vendor/json)
include_directories(${CMAKE_SOURCE_DIR}/engine/src)
include_directories(${CMAKE_SOURCE_DIR}/shared/src)
add_executable(ares_client ${source_client} ${PROTO_SRC} ${PROTO_HDR})

target_link_libraries(ares_client ${SFML_LIBRARIES} jsoncpp)
target_link_libraries(ares_client ares_shared)
target_link_libraries(ares_client ares_engine)
target_link_libraries(ares_client ${PROTOBUF_LIBRARIES})

install(TARGETS ares_client DESTINATION ${CMAKE_INSTALL_PREFIX}/client)
install(DIRECTORY assets DESTINATION ${CMAKE_INSTALL_PREFIX}/client)

