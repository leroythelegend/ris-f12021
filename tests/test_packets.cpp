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

//     try
//     {
//         PacketEvent p(eventpacket);

//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETFORMAT).value(0).UInt == 2021);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMAJORVERSION).value(0).UInt == 1);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMINORVERSION).value(0).UInt == 4);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETVERSION).value(0).UInt == 1);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETID).value(0).UInt == 3);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONUID).value(0).UInt == 14042512579407427396U);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONTIME).value(0).Float == 80.4851379F);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::FRAMEIDENTIFIER).value(0).UInt == 1684);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PLAYERCARINDEX).value(0).UInt == 0);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SECONDARYPLAYERCARINDEX).value(0).UInt == 255);
//         test_assert(p.packets(PacketEvent::Event::EVENT).at(0)->value(PacketEvent::Event::EVENTSTRINGCODE).to_string() == "BUTN");
//         test_assert(p.packets(PacketEvent::Buttons::BUTTONS).at(0)->value(PacketEvent::Buttons::BUTTONSTATUS).value(0).UInt == 4);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//         return 1;
//     }

//     try
//     {
//         PacketCarStatus p(carstatuspacket);

//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETFORMAT).value(0).UInt == 2021);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMAJORVERSION).value(0).UInt == 1);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMINORVERSION).value(0).UInt == 5);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETVERSION).value(0).UInt == 1);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETID).value(0).UInt == 7);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONUID).value(0).UInt == 11396923571662120498U);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONTIME).value(0).Float == 11.7321501F);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::FRAMEIDENTIFIER).value(0).UInt == 240);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PLAYERCARINDEX).value(0).UInt == 0);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SECONDARYPLAYERCARINDEX).value(0).UInt == 255);

//         // loop through number of participants making sure we don't throw.
//         for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
//         {
//             unsigned int a; // stop warning
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::TRACTIONCONTROL).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ANTILOCKBRAKES).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELMIX).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FRONTBRAKEBIAS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::PITLIMITERSTATUS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELINTANK).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELCAPACITY).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELREMAININGLAPS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::MAXRPM).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::IDLERPM).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::MAXGEARS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::DRSALLOWED).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::TYRESAGELAPS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSSTOREENERGY).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSDEPLOYMODE).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::NETWORKPAUSED).value(0).UInt;
//         }

//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::TRACTIONCONTROL).value(0).UInt == 0);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ANTILOCKBRAKES).value(0).UInt == 0);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELMIX).value(0).UInt == 3);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FRONTBRAKEBIAS).value(0).UInt == 58);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::PITLIMITERSTATUS).value(0).UInt == 0);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELINTANK).value(0).Float == 10);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELCAPACITY).value(0).Float == 110);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELREMAININGLAPS).value(0).Float == 5.43956F);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::MAXRPM).value(0).UInt == 13000);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::IDLERPM).value(0).UInt == 3499);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::MAXGEARS).value(0).UInt == 9);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::DRSALLOWED).value(0).UInt == 0);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE).value(0).UInt == 144);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND).value(0).UInt == 17);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND).value(0).UInt == 16);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::TYRESAGELAPS).value(0).UInt == 0);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS).value(0).SInt == 0);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSSTOREENERGY).value(0).Float == 4e+06F);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSDEPLOYMODE).value(0).UInt == 2);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK).value(0).Float == 0);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH).value(0).Float == 0);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP).value(0).Float == 0);
//         test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::NETWORKPAUSED).value(0).UInt == 0);

//         // loop through number of participants making sure we don't throw.
//         for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
//         {
//             unsigned int a; // stop warning
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::TRACTIONCONTROL).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ANTILOCKBRAKES).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELMIX).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FRONTBRAKEBIAS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::PITLIMITERSTATUS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELINTANK).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELCAPACITY).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELREMAININGLAPS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::MAXRPM).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::IDLERPM).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::MAXGEARS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::DRSALLOWED).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::TYRESAGELAPS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSSTOREENERGY).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSDEPLOYMODE).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP).value(0).UInt;
//             a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::NETWORKPAUSED).value(0).UInt;
//         }
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//         return 1;
//     }

//     try
//     {
//         PacketCarTelemetryData p(cartelemetrypacket);

//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETFORMAT).value(0).UInt == 2021);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMAJORVERSION).value(0).UInt == 1);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMINORVERSION).value(0).UInt == 5);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETVERSION).value(0).UInt == 1);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETID).value(0).UInt == 6);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONUID).value(0).UInt == 9712300531107016769U);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONTIME).value(0).Float == 170.670853F);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::FRAMEIDENTIFIER).value(0).UInt == 3675);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PLAYERCARINDEX).value(0).UInt == 0);
//         test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SECONDARYPLAYERCARINDEX).value(0).UInt == 255);

//         // loop through number of participants making sure we don't throw.
//         for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
//         {
//             unsigned int a; // stop warning
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SPEED).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::THROTTLE).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::STEER).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKE).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::CLUTCH).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::GEAR).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::ENGINERPM).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::DRS).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::REVLIGHTSPERCENT).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::REVLIGHTSBITVALUE).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).value(1).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).value(2).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).value(3).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).value(1).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).value(2).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).value(3).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).value(1).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).value(2).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).value(3).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::ENGINETEMPERATURE).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).value(1).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).value(2).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).value(3).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).value(0).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).value(1).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).value(2).UInt;
//             a = p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(i)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).value(3).UInt;
//         }

//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SPEED).value(0).UInt == 253);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::THROTTLE).value(0).Float == 1);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::STEER).value(0).Float == -0.372548938F);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKE).value(0).Float == 0);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::CLUTCH).value(0).UInt == 0);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::GEAR).value(0).SInt == 6);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::ENGINERPM).value(0).UInt == 11600);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::DRS).value(0).UInt == 0);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::REVLIGHTSPERCENT).value(0).UInt == 68);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::REVLIGHTSBITVALUE).value(0).UInt == 2047);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).value(0).UInt == 29);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).value(1).UInt == 29);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).value(2).UInt == 29);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE).value(3).UInt == 29);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).value(0).UInt == 100);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).value(1).UInt == 100);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).value(2).UInt == 100);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE).value(3).UInt == 100);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).value(0).UInt == 100);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).value(1).UInt == 100);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).value(2).UInt == 100);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE).value(3).UInt == 100);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::ENGINETEMPERATURE).value(0).UInt == 90);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).value(0).Float == 23.5738125F);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).value(1).Float == 23.5738125F);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).value(2).Float == 22.6553535F);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE).value(3).Float == 22.6553535F);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).value(0).UInt == 0);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).value(1).UInt == 0);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).value(2).UInt == 0);
//         test_assert(p.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(0)->value(PacketCarTelemetryData::CarTelemetry::SURFACETYPE).value(3).UInt == 0);
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     try
//     {
//         Element test("test");
//         Element nottest("nottest");

//         test_assert(test == test);
//         test_assert(test != nottest);
//         test_assert(test.to_string() == "test");
//         test_assert(nottest.to_string() == "nottest");
//     }
//     catch (const std::exception &e)
//     {
//         std::cerr << e.what() << '\n';
//     }

//     return 0;
}
