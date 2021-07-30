#include <iostream>

#include "tests.h"

#include "../inc/networkfile.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder2bytes.h"
#include "../inc/decoder4bytes.h"
#include "../inc/decoder8bytes.h"

#include "../inc/packetheader.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{

    Bytes eventpacket;

    try
    {
        NetworkFile file("../tests/vectors/event_packet.bin");
        eventpacket = file.read();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        cout << "test decode packet header" << endl;

        // struct PacketHeader
        // {
        //     uint16    m_packetFormat;            // 2021
        //     uint8     m_gameMajorVersion;        // Game major version - "X.00"
        //     uint8     m_gameMinorVersion;        // Game minor version - "1.XX"
        //     uint8     m_packetVersion;           // Version of this packet type, all start from 1
        //     uint8     m_packetId;                // Identifier for the packet type, see below
        //     uint64    m_sessionUID;              // Unique identifier for the session
        //     float     m_sessionTime;             // Session timestamp
        //     uint32    m_frameIdentifier;         // Identifier for the frame the data was retrieved on
        //     uint8     m_playerCarIndex;          // Index of player's car in the array
        //     uint8     m_secondaryPlayerCarIndex; // Index of secondary player's car in the array (splitscreen)
        //                                          // 255 if no second player
        // };

        unsigned int pos = 0;

        Decoder1Byte byte;
        Decoder2Bytes byte2;
        Decoder4Bytes byte4;
        Decoder8Bytes byte8;

        // packet format
        test_assert(byte2.decode(eventpacket, pos).UInt == 2021);

        // game major version

        test_assert(byte.decode(eventpacket, pos).UInt == 1);

        // game minor version

        test_assert(byte.decode(eventpacket, pos).UInt == 4);

        // packet version

        test_assert(byte.decode(eventpacket, pos).UInt == 1);

        // packet id

        test_assert(byte.decode(eventpacket, pos).UInt == 3);

        // session uid

        test_assert(byte8.decode(eventpacket, pos).UInt == 14042512579407427396U);

        // session timestamp

        test_assert(byte4.decode(eventpacket, pos).Float == 80.4851379F);

        // Frame Identifier

        test_assert(byte4.decode(eventpacket, pos).UInt == 1684);

        // player car index

        test_assert(byte.decode(eventpacket, pos).UInt == 0);

        // secondary player index

        test_assert(byte.decode(eventpacket, pos).UInt == 255);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }


    try
    {
        unsigned int pos = 0;
        PacketHeader p(eventpacket, pos);

        test_assert(p.element(1).UInt == 2021);
        test_assert(p.element(2).UInt == 1);
        test_assert(p.element(3).UInt == 4);
        test_assert(p.element(4).UInt == 1);
        test_assert(p.element(5).UInt == 3);
        test_assert(p.element(6).UInt == 14042512579407427396U);
        test_assert(p.element(7).Float == 80.4851379F);
        test_assert(p.element(8).UInt == 1684);
        test_assert(p.element(9).UInt == 0);
        test_assert(p.element(10).UInt == 255);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    

    return 0;
}
