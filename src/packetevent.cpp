#include "../inc/packetevent.h"
#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder4bytes.h"

namespace ris
{
    class Event : public Packet
    {
    public:
        Event(const Bytes &bytes, Pos &pos)
        {
            Elements eventstringcode;
            for (int i = 0; i < 4; ++i)
            {
                eventstringcode.push_back(Decoder1Byte().decode(bytes, pos));
            }

            telemetry_.insert(std::pair<Unit, Elements>(11, eventstringcode));
        }
        ~Event() override = default;
    };

    class Buttons : public Packet
    {
    public:
        Buttons(const Bytes &bytes, Pos &pos)
        {
            telemetry_.insert(std::pair<Unit, Elements>(12, Decoder4Bytes().decode(bytes, pos)));
        }

        ~Buttons() override = default;
    };


    PacketEvent::PacketEvent(const Bytes &bytes, Pos &pos)
    {
        Packet::add(std::make_shared<PacketHeader>(bytes, pos));
        Packet::add(std::make_shared<Event>(bytes, pos));

        // need to make a factory here
        if (PacketComposite::element(11).to_string() == "BUTN")
        {
            Packet::add(std::make_shared<Buttons>(bytes, pos));
        }
    }
} // namespace ris
