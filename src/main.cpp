#include <cstdio>
#include "tools/StringHelper.h"

int main(int argc, char* argv[]) {
    std::string welcomeMessage = "   Hello, World!   ";
    StringHelper::strip(welcomeMessage);
    printf("%s, argc[%d], argv[0]=%s\n", welcomeMessage.c_str(), argc, argv[0]);
    return 0;
}
