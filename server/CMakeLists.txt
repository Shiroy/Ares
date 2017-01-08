set(source_server src/Client.cpp src/Client.h
        src/Entity.cpp src/Entity.h
        src/ListenerThread.cpp src/ListenerThread.h
        src/Main.cpp
        src/Player.cpp src/Player.h
        src/Position.cpp src/Position.h
        src/Reflector.cpp src/Reflector.h
        src/ReflectorValue.cpp src/ReflectorValue.h
        src/Server.cpp src/Server.h
        src/EntityManager.cpp src/EntityManager.h)

find_package(SFML COMPONENTS system network REQUIRED)

find_package(Protobuf REQUIRED)
include_directories(${PROTOBUF_INCLUDE_DIRS})
include_directories(${CMAKE_CURRENT_BINARY_DIR}) #To acces to protobuf generated files with #include <>
file(GLOB_RECURSE proto_files ../protocol/*.proto)
protobuf_generate_cpp(PROTO_SRC PROTO_HDR ${proto_files})

include_directories(${SFML_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/vendor)
include_directories(${CMAKE_SOURCE_DIR}/shared/src)
add_executable(ares_server ${source_server} ${PROTO_SRC} ${PROTO_HDR})

if (UNIX)
    target_link_libraries(ares_server ${SFML_LIBRARIES} pthread)
endif ()

target_link_libraries(ares_server ares_shared)
target_link_libraries(ares_server ${PROTOBUF_LIBRARIES})

install(TARGETS ares_server DESTINATION ${CMAKE_INSTALL_PREFIX}/server)
install(DIRECTORY ../client/assets DESTINATION ${CMAKE_INSTALL_PREFIX}/server)
