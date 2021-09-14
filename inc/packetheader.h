#pragma once

#include <memory>
#include <map>

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketHeader : public SubPacket
    {
    public:
        inline static const Element PACKETFORMAT{"PACKETFORMAT"};
        inline static const Element GAMEMAJORVERSION{"GAMEMAJORVERSION"};
        inline static const Element GAMEMINORVERSION{"GAMEMINORVERSION"};
        inline static const Element PACKETVERSION{"PACKETVERSION"};
        inline static const Element PACKETID{"PACKETID"};
        inline static const Element SESSIONUID{"SESSIONUID"};
        inline static const Element SESSIONTIME{"SESSIONTIME"};
        inline static const Element FRAMEIDENTIFIER{"FRAMEIDENTIFIER"};
        inline static const Element PLAYERCARINDEX{"PLAYERCARINDEX"};
        inline static const Element SECONDARYPLAYERCARINDEX{"SECONDARYPLAYERCARINDEX"};

        inline static const Element PACKETHEADER{"PACKETHEADER"};

        PacketHeader(const Bytes &, Pos &);
        ~PacketHeader() override = default;
    };

} // namespace ris
