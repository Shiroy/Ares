file(GLOB_RECURSE source_server src/*.cpp src/*.h)

find_package(SFML COMPONENTS system network REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
add_executable(ares_server ${source_server})

target_link_libraries(ares_server ${SFML_LIBRARIES})
target_link_libraries(ares_server ares_protocol)
