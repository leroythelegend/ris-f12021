#include <iostream>

#include "tests.h"
#include "../inc/networkfile.h"

#include "../inc/decoderuint16.h"

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
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        cout << "test decoderuint16" << endl;

        DecoderUInt16 decoder;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            decoder.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x10);
        bytes.push_back(0x01);

        decoder.decode(bytes, pos);
        test_assert(decoder.uint() == 272);
        test_assert(pos == 2);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        cout << "test decode event packet" << endl;

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

        DecoderUInt16 packetformat;
        packetformat.decode(eventpacket, pos);
        test_assert(packetformat.uint() == 2021);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
