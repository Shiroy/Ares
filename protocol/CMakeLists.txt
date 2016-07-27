file(GLOB_RECURSE source_protocol src/*.cpp src/*.h)
add_library(ares_protocol STATIC ${source_protocol})
