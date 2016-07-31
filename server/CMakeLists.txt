set(source_server src/Client.cpp src/Client.h
        src/Entity.cpp src/Entity.h
        src/ListenerThread.cpp src/ListenerThread.h
        src/LockedQueue.cpp src/LockedQueue.h
        src/Main.cpp
        src/Player.cpp src/Player.h
        src/Position.cpp src/Position.h
        src/Reflector.cpp src/Reflector.h
        src/ReflectorValue.cpp src/ReflectorValue.h
        src/Server.cpp src/Server.h
        src/EntityManager.cpp src/EntityManager.h)

find_package(SFML COMPONENTS system network REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
add_executable(ares_server ${source_server})

if(UNIX)
    target_link_libraries(ares_server ${SFML_LIBRARIES} pthread)
endif()

target_link_libraries(ares_server ares_protocol)

install(TARGETS ares_server DESTINATION ${CMAKE_INSTALL_PREFIX}/server)
install(DIRECTORY ../client/assets DESTINATION ${CMAKE_INSTALL_PREFIX}/server)
