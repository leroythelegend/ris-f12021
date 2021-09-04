#include <iostream>

#include "tests.h"

#include "../inc/networkfile.h"

#include "../inc/decoderuint8.h"
#include "../inc/decoderint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderuint64.h"
#include "../inc/decoderfloat.h"

#include "../inc/packetheader.h"
#include "../inc/packetevent.h"
#include "../inc/packetcarstatus.h"
#include "../inc/packetcartelemetrydata.h"
#include "../inc/packetsessiondata.h"
#include "../inc/packetsessionhistorydata.h"
#include "../inc/packetlapdata.h"
#include "../inc/packetmotiondata.h"

#include "../inc/element.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{

    Bytes eventpacket;
    Bytes carstatuspacket;
    Bytes cartelemetrypacket;
    Bytes sessionpacket;
    Bytes sessionhistory;
    Bytes lapdata;
    Bytes motiondata;

    try
    {
        NetworkFile e("../tests/vectors/event_packet.bin");
        eventpacket = e.read();
        NetworkFile c("../tests/vectors/car_status.bin");
        carstatuspacket = c.read();
        NetworkFile t("../tests/vectors/car_telemetry.bin");
        cartelemetrypacket = t.read();
        NetworkFile s("../tests/vectors/session_packet.bin");
        sessionpacket = s.read();
        NetworkFile h("../tests/vectors/history_packet.bin");
        sessionhistory = h.read();
        NetworkFile l("../tests/vectors/lap_data.bin");
        lapdata = l.read();
        NetworkFile m("../tests/vectors/motion_data.bin");
        motiondata = m.read();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        cout << "test decode packet header" << endl;

        unsigned int pos = 0;

        DecoderUInt8 duint8;
        DecoderInt8 dint8;
        DecoderUInt16 duint16;
        DecoderInt16 dint16;
        DecoderUInt32 duint32;
        DecoderUInt64 duint64;
        DecoderFloat dfloat;

        // packet format
        test_assert(duint16.decode(eventpacket, pos) == 2021);

        // game major version

        test_assert(duint8.decode(eventpacket, pos) == 1);

        // game minor version

        test_assert(duint8.decode(eventpacket, pos) == 4);

        // packet version

        test_assert(duint8.decode(eventpacket, pos) == 1);

        // packet id

        test_assert(duint8.decode(eventpacket, pos) == 3);

        // session uid

        test_assert(duint64.decode(eventpacket, pos) == 2741612942);

        // session timestamp

        test_assert(dfloat.decode(eventpacket, pos) == 80.485137939453125);

        // Frame Identifier

        test_assert(duint32.decode(eventpacket, pos) == 1684);

        // player car index

        test_assert(duint8.decode(eventpacket, pos) == 0);

        // secondary player index

        test_assert(duint8.decode(eventpacket, pos) == 255);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        unsigned int pos = 0;
        PacketHeader p(eventpacket, pos);

        test_assert(p.telemetry(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.telemetry(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.telemetry(PacketHeader::GAMEMINORVERSION).at(0) == 4);
        test_assert(p.telemetry(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.telemetry(PacketHeader::PACKETID).at(0) == 3);
        test_assert(p.telemetry(PacketHeader::SESSIONUID).at(0) == 2741612942);
        test_assert(p.telemetry(PacketHeader::SESSIONTIME).at(0) == 80.485137939453125);
        test_assert(p.telemetry(PacketHeader::FRAMEIDENTIFIER).at(0) == 1684);
        test_assert(p.telemetry(PacketHeader::PLAYERCARINDEX).at(0) == 0);
        test_assert(p.telemetry(PacketHeader::SECONDARYPLAYERCARINDEX).at(0) == 255);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        PacketEvent p(eventpacket);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMINORVERSION).at(0) == 4);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETID).at(0) == 3);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::SESSIONUID).at(0) == 2741612942);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::SESSIONTIME).at(0) == 80.485137939453125);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::FRAMEIDENTIFIER).at(0) == 1684);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0) == 0);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::SECONDARYPLAYERCARINDEX).at(0) == 255);
        test_assert(p.packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() == "BUTN");
        test_assert(p.packets(PacketEvent::Buttons::BUTTONS).at(0)->telemetry(PacketEvent::Buttons::BUTTONSTATUS).at(0) == 4);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        PacketCarStatus p(carstatuspacket);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMINORVERSION).at(0) == 5);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETID).at(0) == 7);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::SESSIONUID).at(0) == 1125672872);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::SESSIONTIME).at(0) == 11.732150077819824);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::FRAMEIDENTIFIER).at(0) == 240);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0) == 0);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::SECONDARYPLAYERCARINDEX).at(0) == 255);

        // loop through number of participants making sure we don't throw.
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::TRACTIONCONTROL).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::ANTILOCKBRAKES).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::FUELMIX).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::FRONTBRAKEBIAS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::PITLIMITERSTATUS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::FUELINTANK).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::FUELCAPACITY).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::FUELREMAININGLAPS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::MAXRPM).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::IDLERPM).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::MAXGEARS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::DRSALLOWED).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::TYRESAGELAPS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::ERSSTOREENERGY).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::ERSDEPLOYMODE).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->telemetry(PacketCarStatus::CarStatusData::NETWORKPAUSED).at(0);
        }

        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::TRACTIONCONTROL).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::ANTILOCKBRAKES).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::FUELMIX).at(0) == 3);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::FRONTBRAKEBIAS).at(0) == 58);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::PITLIMITERSTATUS).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::FUELINTANK).at(0) == 10);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::FUELCAPACITY).at(0) == 110);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::FUELREMAININGLAPS).at(0) == 5.4395599365234375);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::MAXRPM).at(0) == 13000);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::IDLERPM).at(0) == 3499);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::MAXGEARS).at(0) == 9);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::DRSALLOWED).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE).at(0) == 144);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND).at(0) == 17);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND).at(0) == 16);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::TYRESAGELAPS).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::ERSSTOREENERGY).at(0) == 4000000);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::ERSDEPLOYMODE).at(0) == 2);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->telemetry(PacketCarStatus::CarStatusData::NETWORKPAUSED).at(0) == 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        PacketCarTelemetryData p(cartelemetrypacket);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMINORVERSION).at(0) == 5);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETID).at(0) == 6);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::SESSIONUID).at(0) == 2192684449);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::SESSIONTIME).at(0) == 170.67085266113281);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::FRAMEIDENTIFIER).at(0) == 3675);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0) == 0);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::SECONDARYPLAYERCARINDEX).at(0) == 255);

        // loop through number of participants making sure we don't throw.
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::SPEED).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::THROTTLE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::STEER).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::CLUTCH).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::GEAR).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::ENGINERPM).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::DRS).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::REVLIGHTSPERCENT).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::REVLIGHTSBITVALUE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(3);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(3);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(3);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::ENGINETEMPERATURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(3);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->telemetry(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(3);
        }

        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::SPEED).at(0) == 253);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::THROTTLE).at(0) == 1);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::STEER).at(0) == -0.37254893779754639);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKE).at(0) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::CLUTCH).at(0) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::GEAR).at(0) == 6);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::ENGINERPM).at(0) == 11600);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::DRS).at(0) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::REVLIGHTSPERCENT).at(0) == 68);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::REVLIGHTSBITVALUE).at(0) == 2047);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(0) == 29);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(1) == 29);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(2) == 29);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(3) == 29);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(0) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(1) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(2) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(3) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(0) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(1) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(2) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(3) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::ENGINETEMPERATURE).at(0) == 90);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(0) == 23.573812484741211);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(1) == 23.573812484741211);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(2) == 22.655353546142578);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(3) == 22.655353546142578);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(0) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(1) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(2) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->telemetry(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(3) == 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        PacketSessionData p(sessionpacket);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMINORVERSION).at(0) == 6);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETID).at(0) == 1);

        // loop through number of marshals making sure we don't throw.
        for (int i = 0; i < MAXNUMMARSHALZONES; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketSessionData::MarshalZone::MARSHALZONE).at(i)->telemetry(PacketSessionData::MarshalZone::ZONESTART).at(0);
            a = p.packets(PacketSessionData::MarshalZone::MARSHALZONE).at(i)->telemetry(PacketSessionData::MarshalZone::ZONEFLAG).at(0);
        }

        // loop through number of marshals making sure we don't throw.
        for (int i = 0; i < MAXNUMWEATHERFORECASTSAMPLES; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(i)->telemetry(PacketSessionData::WeatherForecastSample::SESSIONTYPE).at(0);
            a = p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(i)->telemetry(PacketSessionData::WeatherForecastSample::TIMEOFFSET).at(0);
            a = p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(i)->telemetry(PacketSessionData::WeatherForecastSample::WEATHER).at(0);
            a = p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(i)->telemetry(PacketSessionData::WeatherForecastSample::TRACKTEMPERATURE).at(0);
            a = p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(i)->telemetry(PacketSessionData::WeatherForecastSample::TRACKTEMPERATURECHANGE).at(0);
            a = p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(i)->telemetry(PacketSessionData::WeatherForecastSample::AIRTEMPERATURE).at(0);
            a = p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(i)->telemetry(PacketSessionData::WeatherForecastSample::AIRTEMPERATURECHANGE).at(0);
            a = p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(i)->telemetry(PacketSessionData::WeatherForecastSample::RAINPERCENTAGE).at(0);
        }

        test_assert(p.packets(PacketSessionData::MarshalZone::MARSHALZONE).at(0)->telemetry(PacketSessionData::MarshalZone::ZONESTART).at(0) == 0.0024357740767300129);
        test_assert(p.packets(PacketSessionData::MarshalZone::MARSHALZONE).at(0)->telemetry(PacketSessionData::MarshalZone::ZONEFLAG).at(0) == 0);

        test_assert(p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(0)->telemetry(PacketSessionData::WeatherForecastSample::SESSIONTYPE).at(0) == 0);
        test_assert(p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(0)->telemetry(PacketSessionData::WeatherForecastSample::TIMEOFFSET).at(0) == 0);
        test_assert(p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(0)->telemetry(PacketSessionData::WeatherForecastSample::WEATHER).at(0) == 0);
        test_assert(p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(0)->telemetry(PacketSessionData::WeatherForecastSample::TRACKTEMPERATURE).at(0) == 0);
        test_assert(p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(0)->telemetry(PacketSessionData::WeatherForecastSample::TRACKTEMPERATURECHANGE).at(0) == 0);
        test_assert(p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(0)->telemetry(PacketSessionData::WeatherForecastSample::AIRTEMPERATURE).at(0) == 0);
        test_assert(p.packets(PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE).at(0)->telemetry(PacketSessionData::WeatherForecastSample::RAINPERCENTAGE).at(0) == 0);

        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::WEATHER).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::TRACKTEMPERATURE).at(0) == 32);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::AIRTEMPERATURE).at(0) == 24);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::TOTALLAPS).at(0) == 200);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::TRACKLENGTH).at(0) == 5301);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::SESSIONTYPE).at(0) == 13);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::TRACKID).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::FORMULA).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::SESSIONTIMELEFT).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::SESSIONDURATION).at(0) == 600);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::PITSPEEDLIMIT).at(0) == 60);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::GAMEPAUSED).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::ISSPECTATING).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::SPECTATORCARINDEX).at(0) == 255);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::SLIPRONATIVESUPPORT).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::NUMMARSHALZONES).at(0) == 20);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::SAFETYCARSTATUS).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::NETWORKGAME).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::NUMWEATHERFORECASTSAMPLES).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::FORECASTACCURACY).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::AIDIFFICULTY).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::SEASONLINKIDENTIFIER).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::WEEKENDLINKIDENTIFIER).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::SEASONLINKIDENTIFIER).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::PITSTOPWINDOWIDEALLAP).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::PITSTOPWINDOWLATESTLAP).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::PITSTOPREJOINPOSITION).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::STEERINGASSIST).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::BRAKINGASSIST).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::GEARBOXASSIST).at(0) == 1);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::PITASSIST).at(0) == 1);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::PITRELEASEASSIST).at(0) == 1);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::ERSASSIST).at(0) == 1);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::DRSASSIST).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::DYNAMICRACINGLINE).at(0) == 0);
        test_assert(p.packets(PacketSessionData::SessionData::SESSIONDATA).at(0)->telemetry(PacketSessionData::SessionData::DYNAMICRACINGLINETYPE).at(0) == 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        PacketSessionHistoryData p(sessionhistory);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMINORVERSION).at(0) == 6);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETID).at(0) == 11);

        // loop through number of lap histories making sure we don't throw.
        for (int i = 0; i < MAXLAPHISTORY; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(i)->telemetry(PacketSessionHistoryData::LapHistoryData::LAPTIMEINMS).at(0);
            a = p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(i)->telemetry(PacketSessionHistoryData::LapHistoryData::SECTOR1TIMEINMS).at(0);
            a = p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(i)->telemetry(PacketSessionHistoryData::LapHistoryData::SECTOR2TIMEINMS).at(0);
            a = p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(i)->telemetry(PacketSessionHistoryData::LapHistoryData::SECTOR3TIMEINMS).at(0);
            a = p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(i)->telemetry(PacketSessionHistoryData::LapHistoryData::LAPVALIDBITFLAGS).at(0);
        }

        // loop through number of tyre stint history making sure we don't throw.
        for (int i = 0; i < MAXTYRESTINTHISTORY; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketSessionHistoryData::TyreStintHistoryData::TYRESTINTHISTORYDATA).at(i)->telemetry(PacketSessionHistoryData::TyreStintHistoryData::ENDLAP).at(0);
            a = p.packets(PacketSessionHistoryData::TyreStintHistoryData::TYRESTINTHISTORYDATA).at(i)->telemetry(PacketSessionHistoryData::TyreStintHistoryData::TYREACTUALCOMPOUND).at(0);
            a = p.packets(PacketSessionHistoryData::TyreStintHistoryData::TYRESTINTHISTORYDATA).at(i)->telemetry(PacketSessionHistoryData::TyreStintHistoryData::TYREVISUALCOMPOUND).at(0);
        }

        test_assert(p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::LapHistoryData::LAPTIMEINMS).at(0) == 0);
        test_assert(p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::LapHistoryData::SECTOR1TIMEINMS).at(0) == 0);
        test_assert(p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::LapHistoryData::SECTOR2TIMEINMS).at(0) == 0);
        test_assert(p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::LapHistoryData::SECTOR3TIMEINMS).at(0) == 0);
        test_assert(p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::LapHistoryData::LAPVALIDBITFLAGS).at_bitWiseAND(0, 0x01));
        test_assert(p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::LapHistoryData::LAPVALIDBITFLAGS).at_bitWiseAND(0, 0x02));
        test_assert(p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::LapHistoryData::LAPVALIDBITFLAGS).at_bitWiseAND(0, 0x04));
        test_assert(p.packets(PacketSessionHistoryData::LapHistoryData::LAPHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::LapHistoryData::LAPVALIDBITFLAGS).at_bitWiseAND(0, 0x08));

        test_assert(p.packets(PacketSessionHistoryData::TyreStintHistoryData::TYRESTINTHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::TyreStintHistoryData::ENDLAP).at(0) == 255);
        test_assert(p.packets(PacketSessionHistoryData::TyreStintHistoryData::TYRESTINTHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::TyreStintHistoryData::TYREACTUALCOMPOUND).at(0) == 19);
        test_assert(p.packets(PacketSessionHistoryData::TyreStintHistoryData::TYRESTINTHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::TyreStintHistoryData::TYREVISUALCOMPOUND).at(0) == 18);

        test_assert(p.packets(PacketSessionHistoryData::SessionHistoryData::SESSIONHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::SessionHistoryData::CARIDX).at(0) == 10);
        test_assert(p.packets(PacketSessionHistoryData::SessionHistoryData::SESSIONHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::SessionHistoryData::NUMLAPS).at(0) == 1);
        test_assert(p.packets(PacketSessionHistoryData::SessionHistoryData::SESSIONHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::SessionHistoryData::NUMTYRESTINTS).at(0) == 1);
        test_assert(p.packets(PacketSessionHistoryData::SessionHistoryData::SESSIONHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::SessionHistoryData::BESTLAPTIMELAPNUM).at(0) == 0);
        test_assert(p.packets(PacketSessionHistoryData::SessionHistoryData::SESSIONHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::SessionHistoryData::BESTSECTOR1LAPNUM).at(0) == 0);
        test_assert(p.packets(PacketSessionHistoryData::SessionHistoryData::SESSIONHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::SessionHistoryData::BESTSECTOR2LAPNUM).at(0) == 0);
        test_assert(p.packets(PacketSessionHistoryData::SessionHistoryData::SESSIONHISTORYDATA).at(0)->telemetry(PacketSessionHistoryData::SessionHistoryData::BESTSECTOR3LAPNUM).at(0) == 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        PacketLapData p(lapdata);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMINORVERSION).at(0) == 7);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETID).at(0) == 2);

        // loop through number of lap histories making sure we don't throw.
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::LASTLAPTIMEINMS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::SECTOR1TIMEINMS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::SECTOR2TIMEINMS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::TOTALDISTANCE).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::SAFETYCARDELTA).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::CARPOSITION).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::PITSTATUS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::NUMPITSTOPS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::SECTOR).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::CURRENTLAPINVALID).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::PENALTIES).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::WARNINGS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::NUMUNSERVEDDRIVETHROUGHPENS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::NUMUNSERVEDSTOPGOPENS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::GRIDPOSITION).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::DRIVERSTATUS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::RESULTSTATUS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::PITLANETIMERACTIVE).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::PITLANETIMEINLANEINMS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::PITSTOPTIMERINMS).at(0);
            a = p.packets(PacketLapData::LapData::LAPDATA).at(i)->telemetry(PacketLapData::LapData::PITSTOPSHOULDSERVEPEN).at(0);
        }

        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::LASTLAPTIMEINMS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::SECTOR1TIMEINMS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::SECTOR2TIMEINMS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0) == -5456.56787109375);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::TOTALDISTANCE).at(0) == -5456.56787109375);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::SAFETYCARDELTA).at(0) == -0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::CARPOSITION).at(0) == 8);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0) == 1);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::PITSTATUS).at(0) == 1);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::NUMPITSTOPS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::SECTOR).at(0) == 2);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::CURRENTLAPINVALID).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::PENALTIES).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::WARNINGS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::NUMUNSERVEDDRIVETHROUGHPENS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::NUMUNSERVEDSTOPGOPENS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::GRIDPOSITION).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::DRIVERSTATUS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::RESULTSTATUS).at(0) == 2);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::PITLANETIMERACTIVE).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::PITLANETIMEINLANEINMS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::PITSTOPTIMERINMS).at(0) == 0);
        test_assert(p.packets(PacketLapData::LapData::LAPDATA).at(0)->telemetry(PacketLapData::LapData::PITSTOPSHOULDSERVEPEN).at(0) == 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        PacketMotionData p(motiondata);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::GAMEMINORVERSION).at(0) == 8);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PACKETID).at(0) == 0);

        // loop through number of motion data making sure we don't throw.
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDPOSITIONX).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDPOSITIONY).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDPOSITIONZ).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDVELOCITYX).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDVELOCITYY).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDVELOCITYZ).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDFORWARDDIRX).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDFORWARDDIRY).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDFORWARDDIRZ).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDRIGHTDIRX).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDRIGHTDIRY).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::WORLDRIGHTDIRZ).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::GFORCELATERAL).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::GFORCELONGITUDINAL).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::GFORCEVERTICAL).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::YAW).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::PITCH).at(0);
            a = p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(i)->telemetry(PacketMotionData::CarMotionData::ROLL).at(0);
        }

        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDPOSITIONX).at(0) == 22.669370651245117);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDPOSITIONY).at(0) == 3.3167672157287598);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDPOSITIONZ).at(0) == 552.17596435546875);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDVELOCITYX).at(0) == 0);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDVELOCITYY).at(0) == 0);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDVELOCITYZ).at(0) == 0);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDFORWARDDIRX).at(0) == -22788);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDFORWARDDIRY).at(0) == -287);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDFORWARDDIRZ).at(0) == 23542);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDRIGHTDIRX).at(0) == -23543);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDRIGHTDIRY).at(0) == 0);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::WORLDRIGHTDIRZ).at(0) == -22789);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::GFORCELATERAL).at(0) == 0);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::GFORCELONGITUDINAL).at(0) == 0);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::GFORCEVERTICAL).at(0) == 0);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::YAW).at(0) == -0.76910978555679321);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::PITCH).at(0) == -0.006103533785790205);
        test_assert(p.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(0)->telemetry(PacketMotionData::CarMotionData::ROLL).at(0) == -1.2873906598542817e-05);

        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::SUSPENSIONPOSITION).at(0) == 1.6951656341552734);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::SUSPENSIONPOSITION).at(1) == 1.9155979156494141);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::SUSPENSIONPOSITION).at(2) == 9.24957275390625);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::SUSPENSIONPOSITION).at(3) == 9.1767473220825195);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::SUSPENSIONVELOCITY).at(0) == 31.996639251708984);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::SUSPENSIONVELOCITY).at(1) == 32.093448638916016);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::SUSPENSIONVELOCITY).at(2) == 6.7265887260437012);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::SUSPENSIONVELOCITY).at(3) == 5.0883455276489258);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::WHEELSPEED).at(0) == 70.440185546875);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::WHEELSPEED).at(1) == 70.448707580566406);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::WHEELSPEED).at(2) == 70.060035705566406);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::WHEELSPEED).at(3) == 70.064498901367188);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::WHEELSLIP).at(0) == 0.0058781877160072327);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::WHEELSLIP).at(1) == 0.0059530939906835556);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::WHEELSLIP).at(2) == 0.00042044464498758316);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::WHEELSLIP).at(3) == 0.00043327902676537633);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::LOCALVELOCITYX).at(0) == -0.0067737055942416191);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::LOCALVELOCITYY).at(0) == -0.14525362849235535);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::LOCALVELOCITYZ).at(0) == 70.032707214355469);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::ANGULARVELOCITYX).at(0) == 0.00016996217891573906);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::ANGULARVELOCITYY).at(0) == 0.0022311185020953417);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::ANGULARVELOCITYZ).at(0) == -0.015569943934679031);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::ANGULARACCELERATIONX).at(0) == -0.31259262561798096);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::ANGULARACCELERATIONY).at(0) == 0.0033809468150138855);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::ANGULARACCELERATIONZ).at(0) == -0.10543192178010941);
        test_assert(p.packets(PacketMotionData::MotionData::MOTIONDATA).at(0)->telemetry(PacketMotionData::MotionData::FRONTWHEELSANGLE).at(0) == -0);

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        Element test("test");
        Element nottest("nottest");

        test_assert(test == test);
        test_assert(test != nottest);
        test_assert(test.to_string() == "test");
        test_assert(nottest.to_string() == "nottest");
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}
