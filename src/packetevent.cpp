#include "../inc/packetevent.h"
#include "../inc/packetheader.h"

#include "../inc/decoderuint8.h"
#include "../inc/decoderint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderuint64.h"
#include "../inc/decoderfloat.h"

#include <stdexcept>

namespace ris
{

    PacketEvent::FastestLap::FastestLap(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::FastestLap::VEHICLEIDX, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::FastestLap::LAPTIME, {DecoderFloat().decode(bytes, pos)}));
    };

    PacketEvent::Retirement::Retirement(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Retirement::VEHICLEIDX, {DecoderUInt8().decode(bytes, pos)}));
    };

    PacketEvent::TeamMateInPits::TeamMateInPits(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::TeamMateInPits::VEHICLEIDX, {DecoderUInt8().decode(bytes, pos)}));
    };

    PacketEvent::RaceWinner::RaceWinner(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::RaceWinner::VEHICLEIDX, {DecoderUInt8().decode(bytes, pos)}));
    };

    PacketEvent::Penalty::Penalty(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Penalty::PENALTYTYPE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Penalty::INFRINGEMENTTYPE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Penalty::VEHICLEIDX, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Penalty::OTHERVEHICLEIDX, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Penalty::TIME, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Penalty::LAPNUM, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Penalty::PLACESGAINED, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketEvent::SpeedTrap::SpeedTrap(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::SpeedTrap::VEHICLEIDX, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::SpeedTrap::SPEED, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::SpeedTrap::OVERALLFASTESTINSESSION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::SpeedTrap::DRIVERFASTESTINSESSION, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketEvent::StartLights::StartLights(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::StartLights::NUMLIGHTS, {DecoderUInt8().decode(bytes, pos)}));
    };

    PacketEvent::DriveThroughPenaltyServed::DriveThroughPenaltyServed(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::DriveThroughPenaltyServed::VEHICLEIDX, {DecoderUInt8().decode(bytes, pos)}));
    };

    PacketEvent::StopGoPenaltyServed::StopGoPenaltyServed(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::StopGoPenaltyServed::VEHICLEIDX, {DecoderUInt8().decode(bytes, pos)}));
    };

    PacketEvent::Buttons::Buttons(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Buttons::BUTTONSTATUS, {DecoderUInt32().decode(bytes, pos)}));
    };

    PacketEvent::Flashback::Flashback(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Flashback::FLASHBACKFRAMEIDENTIFIER, {DecoderUInt32().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PacketEvent::Flashback::FLASHBACKSESSIONTIME, {DecoderFloat().decode(bytes, pos)}));
    }

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
        else if (eventdetails == "SGSV")
        {
            Packet::add(PacketEvent::StopGoPenaltyServed::STOPGOPENALTYSERVED, SubPackets{std::make_shared<StopGoPenaltyServed>(bytes, pos)});
        }
        else if (eventdetails == "DTSV")
        {
            Packet::add(PacketEvent::DriveThroughPenaltyServed::DRIVETHROUGHPENALTYSERVED, SubPackets{std::make_shared<DriveThroughPenaltyServed>(bytes, pos)});
        }
        else if (eventdetails == "STLG")
        {
            Packet::add(PacketEvent::StartLights::STARTLIGHTS, SubPackets{std::make_shared<StartLights>(bytes, pos)});
        }
        else if (eventdetails == "SPTP")
        {
            Packet::add(PacketEvent::SpeedTrap::SPEEDTRAP, SubPackets{std::make_shared<SpeedTrap>(bytes, pos)});
        }
        else if (eventdetails == "PENA")
        {
            Packet::add(PacketEvent::Penalty::PENALTY, SubPackets{std::make_shared<Penalty>(bytes, pos)});
        }
        else if (eventdetails == "RCWN")
        {
            Packet::add(PacketEvent::RaceWinner::RACEWINNER, SubPackets{std::make_shared<RaceWinner>(bytes, pos)});
        }
        else if (eventdetails == "TMPT")
        {
            Packet::add(PacketEvent::TeamMateInPits::TEAMMATEINPITS, SubPackets{std::make_shared<TeamMateInPits>(bytes, pos)});
        }
        else if (eventdetails == "RTMT")
        {
            Packet::add(PacketEvent::Retirement::RETIREMENT, SubPackets{std::make_shared<Retirement>(bytes, pos)});
        }
        else if (eventdetails == "FTLP")
        {
            Packet::add(PacketEvent::FastestLap::FASTESTLAP, SubPackets{std::make_shared<FastestLap>(bytes, pos)});
        }
        else if (eventdetails == "SSTA" ||
                 eventdetails == "SEND" ||
                 eventdetails == "DRSE" ||
                 eventdetails == "DRSD" ||
                 eventdetails == "CHQF" )
        {
            // do nothing
        }
        else
        {
            // TODO: While creating packets for testing packets we need to skip over this
            // because we don't capture every thing yet, maybe we should just return if we don't know
            // what the packet is, maybe trace it as well.
            // throw std::runtime_error("Unknown event " + eventdetails);
        }
    }

} // namespace ris
