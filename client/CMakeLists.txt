set(source_client
        src/main.cpp
        src/Game.cpp src/Game.h
        src/Player.cpp src/Player.h
        src/PlayerCommands.cpp src/PlayerCommands.h ../engine/src/Character.cpp ../engine/src/Character.h)

find_package(SFML COMPONENTS system window graphics audio network REQUIRED)

include_directories(${SFML_INCLUDE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/vendor/json)
include_directories(${CMAKE_SOURCE_DIR}/engine/src)
add_executable(ares_client ${source_client} src/Game.cpp src/Game.h src/Player.cpp src/Player.h src/PlayerCommands.cpp src/PlayerCommands.h)

target_link_libraries(ares_client ${SFML_LIBRARIES})
target_link_libraries(ares_client ${SFML_LIBRARIES} jsoncpp)
target_link_libraries(ares_client ares_protocol)
target_link_libraries(ares_client ares_engine)

install(TARGETS ares_client DESTINATION ${CMAKE_INSTALL_PREFIX}/client)
install(DIRECTORY assets DESTINATION ${CMAKE_INSTALL_PREFIX}/client)

