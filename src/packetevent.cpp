#include "../inc/packetevent.h"
#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder4bytes.h"

namespace ris
{
    const Element PacketEvent::Buttons::BUTTONSTATUS{"BUTTONSTATUS"};
    const Element PacketEvent::Buttons::BUTTONS{"BUTTONS"};

    PacketEvent::Buttons::Buttons(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Buttons::BUTTONSTATUS, {Decoder4Bytes().decode(bytes, pos), Prefered::UINT}));
    };

    const Element PacketEvent::Flashback::FLASHBACKFRAMEIDENTIFIER{"FLASHBACKFRAMEIDENTIFIER"};
    const Element PacketEvent::Flashback::FLASHBACKSESSIONTIME{"FLASHBACKSESSIONTIME"};
    const Element PacketEvent::Flashback::FLASHBACK{"FLASHBACK"};

    PacketEvent::Flashback::Flashback(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Flashback::FLASHBACKFRAMEIDENTIFIER, {Decoder4Bytes().decode(bytes, pos), Prefered::UINT}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Flashback::FLASHBACKSESSIONTIME, {Decoder4Bytes().decode(bytes, pos), Prefered::FLOAT}));
    }

    const Element PacketEvent::Event::EVENTSTRINGCODE{"EVENTSTRINGCODE"};
    const Element PacketEvent::Event::EVENT{"EVENT"};

    PacketEvent::Event::Event(const Bytes &bytes, Pos &pos)
    {
        Values eventstringcode;
        for (int i = 0; i < 4; ++i)
        {
            eventstringcode.push_back(Decoder1Byte().decode(bytes, pos), Prefered::UINT);
        }

        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Event::EVENTSTRINGCODE, eventstringcode));
    }

    PacketEvent::PacketEvent(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, std::vector<Packet::Ptr>{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(PacketEvent::Event::EVENT, std::vector<Packet::Ptr>{std::make_shared<Event>(bytes, pos)});

        addCorrectEventDetailsToPacket(bytes, pos);
    }

    void PacketEvent::addCorrectEventDetailsToPacket(const Bytes &bytes, Pos &pos)
    {
        std::string eventdetails = packets(Event::EVENT).at(0)->value(Event::EVENTSTRINGCODE).to_string();
        if (eventdetails == "BUTN")
        {
            Packet::add(PacketEvent::Buttons::BUTTONS, std::vector<Packet::Ptr>{std::make_shared<Buttons>(bytes, pos)});
        }
        else if (eventdetails == "FLBK")
        {
            Packet::add(PacketEvent::Flashback::FLASHBACK, std::vector<Packet::Ptr>{std::make_shared<Flashback>(bytes, pos)});
        }
    }

} // namespace ris
