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

    const Element PacketHeader::PACKETFORMAT{"PACKETFORMAT"};
    const Element PacketHeader::GAMEMAJORVERSION{"GAMEMAJORVERSION"};
    const Element PacketHeader::GAMEMINORVERSION{"GAMEMINORVERSION"};
    const Element PacketHeader::PACKETVERSION{"PACKETVERSION"};
    const Element PacketHeader::PACKETID{"PACKETID"};
    const Element PacketHeader::SESSIONUID{"SESSIONUID"};
    const Element PacketHeader::SESSIONTIME{"SESSIONTIME"};
    const Element PacketHeader::FRAMEIDENTIFIER{"FRAMEIDENTIFIER"};
    const Element PacketHeader::PLAYERCARINDEX{"PLAYERCARINDEX"};
    const Element PacketHeader::SECONDARYPLAYERCARINDEX{"SECONDARYPLAYERCARINDEX"};

    PacketHeader::PacketHeader(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PACKETFORMAT, Decoder2Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(GAMEMAJORVERSION, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(GAMEMINORVERSION, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(PACKETVERSION, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(PACKETID, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(SESSIONUID, Decoder8Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(SESSIONTIME, Decoder4Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(FRAMEIDENTIFIER, Decoder4Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(PLAYERCARINDEX, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(SECONDARYPLAYERCARINDEX, Decoder1Byte().decode(bytes, pos)));
    }
} // namespace ris
