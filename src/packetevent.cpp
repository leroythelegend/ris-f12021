#include "../inc/packetevent.h"

namespace ris
{
    PacketEvent::PacketEvent()
    {
        for (int i = 0; i < 4; ++i)
        {
            eventstringcode_.push_back(std::make_shared<DecoderUInt8>());
        }

        for (auto eventstringcode : eventstringcode_)
        {
            decoders_.push_back(eventstringcode);
        }
    }

    void PacketEvent::decode(const Bytes &bytes, Pos &pos)
    {
        packetheader_.decode(bytes, pos);
        Packet::decode(bytes, pos);
    }

    PacketHeader PacketEvent::packetHeader() const
    {
        return packetheader_;
    }

    PacketEvent::Event PacketEvent::eventStringCode() const
    {
        Event event;
        for (auto eventstringcode : eventstringcode_)
        {
            event.append(1, (char)eventstringcode->uint());
        }

        return event;
    }

} // namespace ris
