#include "../inc/networkudp.h"
#include "../inc/packetheader.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{
    ris::NetworkUDP network(20777);

    ris::Bytes bytes = network.read();

    // just want to create some test vectors so write to file
    // then I will subclass a NetworkFile from Network to test
    // decoders

    // maybe able to get rid of the expicit pos?
    // for now don't capture the event packet because
    // we already have one but we will capture the other 
    // parts of the event packet later.
    Pos pos = 0;
    if (PacketHeader(bytes, pos).value(PacketHeader::PACKETID).at(0).UInt != (unsigned int)PacketID::Event)
    {
        ofstream outfile("/tmp/f12021.out", ios::out|ios::binary);
        cout << "captured size " << bytes.size() << endl;
        outfile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
    }
    return 0;
}
