#include <google/protobuf/stubs/common.h>
#include "Server.h"

int main() {

    Server::getInstance().run();
    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
