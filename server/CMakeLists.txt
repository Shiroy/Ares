file(GLOB_RECURSE source_server src/*.cpp src/*.h)

find_package(SFML COMPONENTS system network REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
add_executable(ares_server ${source_server})

if(UNIX)
    target_link_libraries(ares_server ${SFML_LIBRARIES} pthread)
endif()

target_link_libraries(ares_server ares_protocol)

install(TARGETS ares_server DESTINATION ${CMAKE_INSTALL_PREFIX}/server)
install(DIRECTORY ../client/assets DESTINATION ${CMAKE_INSTALL_PREFIX}/server)
