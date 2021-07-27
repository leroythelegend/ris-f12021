#pragma once

#include <vector>
#include <string>

#include "../inc/packet.h"
#include "../inc/packetheader.h"

#include "../inc/decoderfloat.h"
#include "../inc/decoderuint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderuint64.h"

namespace ris
{

    class PacketEvent : public Packet
    {
    public:

        using Event = std::string;

        PacketEvent();
        ~PacketEvent() = default;      

        void decode(const Bytes &, Pos &) override;

        PacketHeader packetHeader() const;
        Event eventStringCode() const;

    private:
        PacketHeader packetheader_;

        std::vector<Decoder::Ptr> eventstringcode_;
    };

} // namespace ris
