#include <google/protobuf/stubs/common.h>
#include "Server.h"

int main() {

    Server s;
    s.run();

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
