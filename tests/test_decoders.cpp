#include <iostream>

#include "../inc/networkfile.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{
    cout << "test decoders" << endl;

    Bytes eventpacket;

    try
    {
        NetworkFile file("../tests/vectors/event_packet.bin");
        eventpacket = file.read();       
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    

    return 0;
}
