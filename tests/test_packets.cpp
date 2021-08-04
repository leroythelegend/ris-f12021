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

#include "../inc/element.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{

    Bytes eventpacket;
    Bytes carstatuspacket;
    Bytes cartelemetrypacket;

    try
    {
        NetworkFile e("../tests/vectors/event_packet.bin");
        eventpacket = e.read();
        NetworkFile c("../tests/vectors/car_status.bin");
        carstatuspacket = c.read();
        NetworkFile t("../tests/vectors/car_telemetry.bin");
        cartelemetrypacket = t.read();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
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
    }

    try
    {
        unsigned int pos = 0;
        PacketHeader p(eventpacket, pos);

        test_assert(p.value(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.value(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.value(PacketHeader::GAMEMINORVERSION).at(0) == 4);
        test_assert(p.value(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.value(PacketHeader::PACKETID).at(0) == 3);
        test_assert(p.value(PacketHeader::SESSIONUID).at(0) == 2741612942);
        test_assert(p.value(PacketHeader::SESSIONTIME).at(0) == 80.485137939453125);
        test_assert(p.value(PacketHeader::FRAMEIDENTIFIER).at(0) == 1684);
        test_assert(p.value(PacketHeader::PLAYERCARINDEX).at(0) == 0);
        test_assert(p.value(PacketHeader::SECONDARYPLAYERCARINDEX).at(0) == 255);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        PacketEvent p(eventpacket);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMINORVERSION).at(0) == 4);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETID).at(0) == 3);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONUID).at(0) == 2741612942);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONTIME).at(0) == 80.485137939453125);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::FRAMEIDENTIFIER).at(0) == 1684);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PLAYERCARINDEX).at(0) == 0);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SECONDARYPLAYERCARINDEX).at(0) == 255);
        test_assert(p.packets(PacketEvent::Event::EVENT).at(0)->value(PacketEvent::Event::EVENTSTRINGCODE).to_string() == "BUTN");
        test_assert(p.packets(PacketEvent::Buttons::BUTTONS).at(0)->value(PacketEvent::Buttons::BUTTONSTATUS).at(0) == 4);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        PacketCarStatus p(carstatuspacket);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMINORVERSION).at(0) == 5);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETID).at(0) == 7);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONUID).at(0) == 1125672872);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONTIME).at(0) == 11.732150077819824);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::FRAMEIDENTIFIER).at(0) == 240);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PLAYERCARINDEX).at(0) == 0);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SECONDARYPLAYERCARINDEX).at(0) == 255);

        // loop through number of participants making sure we don't throw.
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::TRACTIONCONTROL).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ANTILOCKBRAKES).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELMIX).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FRONTBRAKEBIAS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::PITLIMITERSTATUS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELINTANK).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELCAPACITY).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELREMAININGLAPS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::MAXRPM).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::IDLERPM).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::MAXGEARS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::DRSALLOWED).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::TYRESAGELAPS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSSTOREENERGY).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSDEPLOYMODE).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP).at(0);
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::NETWORKPAUSED).at(0);
        }

        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::TRACTIONCONTROL).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ANTILOCKBRAKES).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELMIX).at(0) == 3);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FRONTBRAKEBIAS).at(0) == 58);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::PITLIMITERSTATUS).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELINTANK).at(0) == 10);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELCAPACITY).at(0) == 110);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELREMAININGLAPS).at(0) == 5.4395599365234375);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::MAXRPM).at(0) == 13000);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::IDLERPM).at(0) == 3499);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::MAXGEARS).at(0) == 9);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::DRSALLOWED).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE).at(0) == 144);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND).at(0) == 17);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND).at(0) == 16);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::TYRESAGELAPS).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSSTOREENERGY).at(0) == 4000000);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSDEPLOYMODE).at(0) == 2);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP).at(0) == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::NETWORKPAUSED).at(0) == 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        PacketCarTelemetryData p(cartelemetrypacket);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETFORMAT).at(0) == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMAJORVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMINORVERSION).at(0) == 5);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETVERSION).at(0) == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETID).at(0) == 6);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONUID).at(0) == 2192684449);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONTIME).at(0) == 170.67085266113281);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::FRAMEIDENTIFIER).at(0) == 3675);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PLAYERCARINDEX).at(0) == 0);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SECONDARYPLAYERCARINDEX).at(0) == 255);

        // loop through number of participants making sure we don't throw.
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            double a; // stop warning
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SPEED).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::THROTTLE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::STEER).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::CLUTCH).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::GEAR).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::ENGINERPM).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::DRS).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::REVLIGHTSPERCENT).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::REVLIGHTSBITVALUE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(3);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(3);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(3);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::ENGINETEMPERATURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(3);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(0);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(1);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(2);
            a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(3);
        }

        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SPEED).at(0) == 253);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::THROTTLE).at(0) == 1);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::STEER).at(0) == -0.37254893779754639);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKE).at(0) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::CLUTCH).at(0) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::GEAR).at(0) == 6);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::ENGINERPM).at(0) == 11600);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::DRS).at(0) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::REVLIGHTSPERCENT).at(0) == 68);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::REVLIGHTSBITVALUE).at(0) == 2047);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(0) == 29);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(1) == 29);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(2) == 29);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).at(3) == 29);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(0) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(1) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(2) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).at(3) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(0) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(1) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(2) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).at(3) == 100);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::ENGINETEMPERATURE).at(0) == 90);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(0) == 23.573812484741211);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(1) == 23.573812484741211);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(2) == 22.655353546142578);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).at(3) == 22.655353546142578);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(0) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(1) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(2) == 0);
        test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).at(3) == 0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
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
    }

    return 0;
}
