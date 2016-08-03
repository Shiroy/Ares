set(source_engine src/Entity.cpp src/Entity.h
        src/TextureManager.cpp src/TextureManager.h
        src/Tilemap.cpp src/Tilemap.h src/MathUtil.h
        src/AnimatedSprite.cpp src/AnimatedSprite.h
        src/SpriteAnimation.cpp src/SpriteAnimation.h
        src/AnimatedSpriteCharacter.cpp src/AnimatedSpriteCharacter.h src/QuadTree.cpp src/QuadTree.h)

include_directories(${CMAKE_SOURCE_DIR}/vendor/json)

add_library(ares_engine STATIC ${source_engine})