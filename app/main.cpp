#include "../inc/networkudp.h"

#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    ris::NetworkUDP network(5505);

    ris::Bytes bytes = network.read(1024);

    return 0;
}
