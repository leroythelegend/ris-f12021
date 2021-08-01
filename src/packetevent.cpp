#include "../inc/packetevent.h"
#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder4bytes.h"

namespace ris
{

    const Element PacketEvent::EVENTSTRINGCODE{"EVENTSTRINGCODE"};

    class Event : public Packet
    {
    public:
        Event(const Bytes &bytes, Pos &pos)
        {
            Values eventstringcode;
            for (int i = 0; i < 4; ++i)
            {
                eventstringcode.push_back(Decoder1Byte().decode(bytes, pos));
            }

            telemetry_.insert(std::pair<Element, Values>(PacketEvent::EVENTSTRINGCODE, eventstringcode));
        }
        ~Event() override = default;
    };

    const Element PacketEvent::Buttons::BUTTONSTATUS{"BUTTONSTATUS"};
    const Element PacketEvent::Buttons::BUTTONS{"BUTTONS"};

    PacketEvent::Buttons::Buttons(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Buttons::BUTTONSTATUS, Decoder4Bytes().decode(bytes, pos)));
    };

    PacketEvent::PacketEvent(const Bytes &bytes, Pos &pos)
    {
        Packet::add(PacketHeader::PACKETHEADER, std::vector<Packet::Ptr>{std::make_shared<PacketHeader>(bytes, pos)});
        
        addEventStringCodeToTelemetry(bytes, pos);

        // need to make a factory here
        if (value(EVENTSTRINGCODE).to_string() == "BUTN")
        {
            Packet::add(PacketEvent::Buttons::BUTTONS, std::vector<Packet::Ptr>{std::make_shared<Buttons>(bytes, pos)});
        }
    }

    void PacketEvent::addEventStringCodeToTelemetry(const Bytes &bytes, Pos &pos)
    {
        Values eventstringcode;
        for (int i = 0; i < 4; ++i)
        {
            eventstringcode.push_back(Decoder1Byte().decode(bytes, pos));
        }

        telemetry_.insert(std::pair<Element, Values>(PacketEvent::EVENTSTRINGCODE, eventstringcode));
    }

} // namespace ris
