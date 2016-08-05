set(source_engine src/Entity.cpp src/Entity.h
        src/TextureManager.cpp src/TextureManager.h
        src/Tilemap.cpp src/Tilemap.h src/MathUtil.h
        src/AnimatedSprite.cpp src/AnimatedSprite.h
        src/SpriteAnimation.cpp src/SpriteAnimation.h
        src/AnimatedSpriteCharacter.cpp src/AnimatedSpriteCharacter.h
        src/QuadTree.cpp src/QuadTree.h
        src/Character.cpp src/Character.h
        src/AnimatedSpritesUpdater.cpp src/AnimatedSpritesUpdater.h
        src/EntityManager.cpp src/EntityManager.h
        src/Player.cpp src/Player.h src/AresException.cpp src/AresException.h)

include_directories(${CMAKE_SOURCE_DIR}/vendor/json)
include_directories(${CMAKE_SOURCE_DIR}/shared/src)
include_directories(${SFML_INCLUDE_DIR})

add_library(ares_engine STATIC ${source_engine})