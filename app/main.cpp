#include "../inc/networkudp.h"
#include "../inc/packetheader.h"
#include "../inc/packetevent.h"

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

    // for now don't capture the event or car status packets because
    // we already have them but we will capture the other
    // parts of the event packet later.
    Pos pos = 0;
    unsigned int packetid = PacketHeader(bytes, pos).value(PacketHeader::PACKETID).at(0).UInt;

    if (packetid != (unsigned int)PacketID::Event &&
        packetid != (unsigned int)PacketID::Car_Status )
    {
        ofstream outfile("/tmp/f12021.out", ios::out | ios::binary);
        cout << "not event captured size " << bytes.size() << endl;
        outfile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
    }
    else
    {
        pos = 0;
        if (PacketEvent(bytes, pos).value(PacketEvent::EVENTSTRINGCODE).to_string() != "BUTN")
        {
            ofstream outfile("/tmp/event.out", ios::out | ios::binary);
            cout << "event captured size " << 
                    bytes.size() << " " << 
                    PacketEvent(bytes, pos).value(PacketEvent::EVENTSTRINGCODE).to_string() << endl;
            outfile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
        }
    }
    return 0;
}
