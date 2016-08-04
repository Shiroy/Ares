set(source_shared src/LockedQueue.cpp src/LockedQueue.h)

include_directories(${SFML_INCLUDE_DIR})

add_library(ares_shared STATIC ${source_shared})
