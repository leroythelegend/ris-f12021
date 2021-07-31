#include "../inc/packetevent.h"
#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"

namespace ris
{
    class Event : public Packet
    {
    public:
        Event(const Bytes &bytes, Pos &pos)
        {
            Decoder1Byte decoderonebyte;
            Elements eventstringcode;
            for (int i = 0; i < 4; ++i)
            {
                eventstringcode.push_back(decoderonebyte.decode(bytes, pos));
            }

            telemetry_.insert(std::pair<Unit, Elements>(11, eventstringcode));
        }
    };
    PacketEvent::PacketEvent(const Bytes &bytes, Pos &pos)
    {
        Packet::add(std::make_shared<PacketHeader>(bytes, pos));
        Packet::add(std::make_shared<Event>(bytes, pos));
    }
} // namespace ris
