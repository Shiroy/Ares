#include <google/protobuf/stubs/common.h>
#include "Game.h"

int main() {
    Game game;
    game.run();

    google::protobuf::ShutdownProtobufLibrary();
}
