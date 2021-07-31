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
        Decoder1Byte decoderonebyte;
        Decoder2Bytes decodertwobytes;
        Decoder4Bytes decoderfourbytes;
        Decoder8Bytes decodereightbytes;

        telemetry_.insert(std::pair<Unit, Elements>(1, decodertwobytes.decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Elements>(2, decoderonebyte.decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Elements>(3, decoderonebyte.decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Elements>(4, decoderonebyte.decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Elements>(5, decoderonebyte.decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Elements>(6, decodereightbytes.decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Elements>(7, decoderfourbytes.decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Elements>(8, decoderfourbytes.decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Elements>(9, decoderonebyte.decode(bytes, pos)));
        telemetry_.insert(std::pair<Unit, Elements>(10, decoderonebyte.decode(bytes, pos)));
    }
} // namespace ris
