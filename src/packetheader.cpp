#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder2bytes.h"
#include "../inc/decoder4bytes.h"
#include "../inc/decoder8bytes.h"

namespace ris
{

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

    PacketHeader::PacketHeader(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Unit, Values>(1, Decoder2Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Values>(2, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Values>(3, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Values>(4, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Values>(5, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Values>(6, Decoder8Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Values>(7, Decoder4Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Values>(8, Decoder4Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Values>(9, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Values>(10, Decoder1Byte().decode(bytes, pos)));
    }
} // namespace ris
