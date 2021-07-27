#include <iostream>

#include "tests.h"

#include "../inc/networkfile.h"
#include "../inc/decoderuint64.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderuint8.h"
#include "../inc/decoderfloat.h"
#include "../inc/packetheader.h"
#include "../inc/packetevent.h"

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

        DecoderUInt8 uint8;
        DecoderUInt16 uint16;
        DecoderUInt32 uint32;
        DecoderUInt64 uint64;
        DecoderFloat float32;

        // packet format
        uint16.decode(eventpacket, pos);
        test_assert(uint16.uint() == 2021);

        // game major version
        uint8.decode(eventpacket, pos);
        test_assert(uint8.uint() == 1);

        // game minor version
        uint8.decode(eventpacket, pos);
        test_assert(uint8.uint() == 4);

        // packet version
        uint8.decode(eventpacket, pos);
        test_assert(uint8.uint() == 1);

        // packet id
        uint8.decode(eventpacket, pos);
        test_assert(uint8.uint() == 3);

        // session uid
        uint64.decode(eventpacket, pos);
        test_assert(uint64.uint() == 14042512579407427396U);

        // session timestamp
        float32.decode(eventpacket, pos);
        test_assert(float32.float32() == 80.4851379F);

        // Frame Identifier
        uint32.decode(eventpacket, pos);
        test_assert(uint32.uint() == 1684);

        // player car index
        uint8.decode(eventpacket, pos);
        test_assert(uint8.uint() == 0);

        // secondary player index
        uint8.decode(eventpacket, pos);
        test_assert(uint8.uint() == 255);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        PacketHeader decoder;

        unsigned int pos = 0;
        decoder.decode(eventpacket, pos);

        test_assert(decoder.packetFormat() == 2021);
        test_assert(decoder.gameMajorVersion() == 1);
        test_assert(decoder.gameMinorVersion() == 4);
        test_assert(decoder.packetVersion() == 1);
        test_assert(decoder.packetID() == 3);
        test_assert(decoder.sessionUID() == 14042512579407427396U);
        test_assert(decoder.sessionTime() == 80.4851379F);
        test_assert(decoder.frameIdentifier() == 1684);
        test_assert(decoder.playerCarIndex() == 0);
        test_assert(decoder.secondaryPlayerCarIndex() == 255);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        PacketEvent decoder;

        unsigned int pos = 0;
        decoder.decode(eventpacket, pos);

        test_assert(decoder.packetHeader().packetFormat() == 2021);
        test_assert(decoder.packetHeader().gameMajorVersion() == 1);
        test_assert(decoder.packetHeader().gameMinorVersion() == 4);
        test_assert(decoder.packetHeader().packetVersion() == 1);
        test_assert(decoder.packetHeader().packetID() == 3);
        test_assert(decoder.packetHeader().sessionUID() == 14042512579407427396U);
        test_assert(decoder.packetHeader().sessionTime() == 80.4851379F);
        test_assert(decoder.packetHeader().frameIdentifier() == 1684);
        test_assert(decoder.packetHeader().playerCarIndex() == 0);
        test_assert(decoder.packetHeader().secondaryPlayerCarIndex() == 255);

        cout << decoder.eventStringCode() << endl;

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    

    return 0;
}
