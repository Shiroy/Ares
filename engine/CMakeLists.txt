file(GLOB_RECURSE source_engine src/*.cpp src/*.h)
add_library(ares_engine STATIC ${source_engine})
