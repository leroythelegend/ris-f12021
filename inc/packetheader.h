#pragma once

#include <memory>
#include <map>

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketHeader : public Packet
    {
    public:
        static const Element PACKETFORMAT;
        static const Element GAMEMAJORVERSION;
        static const Element GAMEMINORVERSION;
        static const Element PACKETVERSION;
        static const Element PACKETID;
        static const Element SESSIONUID;
        static const Element SESSIONTIME;
        static const Element FRAMEIDENTIFIER;
        static const Element PLAYERCARINDEX;
        static const Element SECONDARYPLAYERCARINDEX;

        static const Element PACKETHEADER;

        PacketHeader(const Bytes &, Pos &);
        ~PacketHeader() override = default;
    };

} // namespace ris
