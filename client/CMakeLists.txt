file(GLOB_RECURSE source_client src/*.cpp src/*.h)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
add_executable(ares_client ${source_client})

target_link_libraries(ares_client ${SFML_LIBRARIES})
target_link_libraries(ares_client ares_protocol)
target_link_libraries(ares_client ares_engine)
