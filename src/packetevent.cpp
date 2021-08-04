#include "../inc/packetevent.h"
#include "../inc/packetheader.h"

#include "../inc/decoderuint8.h"
#include "../inc/decoderint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderuint64.h"
#include "../inc/decoderfloat.h"

namespace ris
{
    const Element PacketEvent::Buttons::BUTTONSTATUS{"BUTTONSTATUS"};
    const Element PacketEvent::Buttons::BUTTONS{"BUTTONS"};

    PacketEvent::Buttons::Buttons(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Buttons::BUTTONSTATUS, {DecoderUInt32().decode(bytes, pos)}));
    };

    const Element PacketEvent::Flashback::FLASHBACKFRAMEIDENTIFIER{"FLASHBACKFRAMEIDENTIFIER"};
    const Element PacketEvent::Flashback::FLASHBACKSESSIONTIME{"FLASHBACKSESSIONTIME"};
    const Element PacketEvent::Flashback::FLASHBACK{"FLASHBACK"};

    PacketEvent::Flashback::Flashback(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Flashback::FLASHBACKFRAMEIDENTIFIER, {DecoderUInt32().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Flashback::FLASHBACKSESSIONTIME, {DecoderFloat().decode(bytes, pos)}));
    }

    const Element PacketEvent::Event::EVENTSTRINGCODE{"EVENTSTRINGCODE"};
    const Element PacketEvent::Event::EVENT{"EVENT"};

    PacketEvent::Event::Event(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Event::EVENTSTRINGCODE, DecoderUInt8().decode(bytes, pos, 4)));
    }

    PacketEvent::PacketEvent(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(PacketEvent::Event::EVENT, SubPackets{std::make_shared<Event>(bytes, pos)});

        addCorrectEventDetailsToPacket(bytes, pos);
    }

    void PacketEvent::addCorrectEventDetailsToPacket(const Bytes &bytes, Pos &pos)
    {
        std::string eventdetails = packets(Event::EVENT).at(0)->telemetry(Event::EVENTSTRINGCODE).to_string();
        if (eventdetails == "BUTN")
        {
            Packet::add(PacketEvent::Buttons::BUTTONS, SubPackets{std::make_shared<Buttons>(bytes, pos)});
        }
        else if (eventdetails == "FLBK")
        {
            Packet::add(PacketEvent::Flashback::FLASHBACK, SubPackets{std::make_shared<Flashback>(bytes, pos)});
        }
    }

} // namespace ris
