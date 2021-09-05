#include "../inc/networkudp.h"
#include "../inc/packetheader.h"
#include "../inc/packetevent.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{
    try
    {
        ris::NetworkUDP network(20777);

        while (true)
        {
            ris::Bytes bytes = network.read();

            // just want to create some test vectors so write to file
            // then I will subclass a NetworkFile from Network to test
            // decoders

            // for now don't capture the event or car status packets because
            // we already have them but we will capture the other
            // parts of the event packet later.
            unsigned int packetid = (unsigned int)bytes.at(5);

            if (packetid != (unsigned int)PacketID::Event &&
                packetid != (unsigned int)PacketID::Car_Status &&
                packetid != (unsigned int)PacketID::Car_Telemetry &&
                packetid != (unsigned int)PacketID::Session_History &&
                packetid != (unsigned int)PacketID::Session &&
                packetid != (unsigned int)PacketID::Lap_Data &&
                packetid != (unsigned int)PacketID::Motion &&
                packetid != (unsigned int)PacketID::Car_Setups &&
                packetid != (unsigned int)PacketID::Car_Damage
                )
            {
                ofstream outfile("/tmp/f12021.out", ios::out | ios::binary);
                cout << "not event captured size " << bytes.size() << endl;
                outfile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
                return 1;
            }
            // else
            // {
            //     if (PacketEvent(bytes).packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() != "BUTN" ||
            //         !PacketEvent(bytes).packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string().empty())
            //     {
            //         ofstream outfile("/tmp/event.out", ios::out | ios::binary);
            //         cout << "event captured size " << bytes.size() << " " << PacketEvent(bytes).packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() << endl;
            //         outfile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
            //         return 1;
            //     }
            // }
        }
    }
    catch (std::exception &e)
    {
        cout << "ERROR " << e.what() << endl;
    }
    catch (...)
    {
        cout << "no idea" << endl;

    }
    return 0;
}
