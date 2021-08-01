#include <iostream>

#include "tests.h"

#include "../inc/networkfile.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder2bytes.h"
#include "../inc/decoder4bytes.h"
#include "../inc/decoder8bytes.h"

#include "../inc/packetheader.h"
#include "../inc/packetevent.h"
#include "../inc/packetcarstatus.h"

#include "../inc/element.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{

    Bytes eventpacket;
    Bytes carstatuspacket;

    try
    {
        NetworkFile e("../tests/vectors/event_packet.bin");
        eventpacket = e.read();
        NetworkFile c("../tests/vectors/car_status.bin");
        carstatuspacket = c.read();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        cout << "test decode packet header" << endl;

        // struct PacketHeader
        // {
        //     uint16    m_packetFormat;            // 2021
        //     uint8     m_gameMajorVersion;        // Game major version - "X.00"
        //     uint8     m_gameMinorVersion;        // Game minor version - "1.XX"
        //     uint8     m_packetVersion;           // Version of this packet type, all start from 1
        //     uint8     m_packetId;                // Identifier for the packet type, see below
        //     uint64    m_sessionUID;              // Unique identifier for the session
        //     float     m_sessionTime;             // Session timestamp
        //     uint32    m_frameIdentifier;         // Identifier for the frame the data was retrieved on
        //     uint8     m_playerCarIndex;          // Index of player's car in the array
        //     uint8     m_secondaryPlayerCarIndex; // Index of secondary player's car in the array (splitscreen)
        //                                          // 255 if no second player
        // };

        unsigned int pos = 0;

        Decoder1Byte byte;
        Decoder2Bytes byte2;
        Decoder4Bytes byte4;
        Decoder8Bytes byte8;

        // packet format
        test_assert(byte2.decode(eventpacket, pos).UInt == 2021);

        // game major version

        test_assert(byte.decode(eventpacket, pos).UInt == 1);

        // game minor version

        test_assert(byte.decode(eventpacket, pos).UInt == 4);

        // packet version

        test_assert(byte.decode(eventpacket, pos).UInt == 1);

        // packet id

        test_assert(byte.decode(eventpacket, pos).UInt == 3);

        // session uid

        test_assert(byte8.decode(eventpacket, pos).UInt == 14042512579407427396U);

        // session timestamp

        test_assert(byte4.decode(eventpacket, pos).Float == 80.4851379F);

        // Frame Identifier

        test_assert(byte4.decode(eventpacket, pos).UInt == 1684);

        // player car index

        test_assert(byte.decode(eventpacket, pos).UInt == 0);

        // secondary player index

        test_assert(byte.decode(eventpacket, pos).UInt == 255);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        unsigned int pos = 0;
        PacketHeader p(eventpacket, pos);

        test_assert(p.value(PacketHeader::PACKETFORMAT).at(0).UInt == 2021);
        test_assert(p.value(PacketHeader::GAMEMAJORVERSION).at(0).UInt == 1);
        test_assert(p.value(PacketHeader::GAMEMINORVERSION).at(0).UInt == 4);
        test_assert(p.value(PacketHeader::PACKETVERSION).at(0).UInt == 1);
        test_assert(p.value(PacketHeader::PACKETID).at(0).UInt == 3);
        test_assert(p.value(PacketHeader::SESSIONUID).at(0).UInt == 14042512579407427396U);
        test_assert(p.value(PacketHeader::SESSIONTIME).at(0).Float == 80.4851379F);
        test_assert(p.value(PacketHeader::FRAMEIDENTIFIER).at(0).UInt == 1684);
        test_assert(p.value(PacketHeader::PLAYERCARINDEX).at(0).UInt == 0);
        test_assert(p.value(PacketHeader::SECONDARYPLAYERCARINDEX).at(0).UInt == 255);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        unsigned int pos = 0;
        PacketEvent p(eventpacket, pos);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETFORMAT).at(0).UInt == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMAJORVERSION).at(0).UInt == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMINORVERSION).at(0).UInt == 4);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETVERSION).at(0).UInt == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETID).at(0).UInt == 3);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONUID).at(0).UInt == 14042512579407427396U);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONTIME).at(0).Float == 80.4851379F);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::FRAMEIDENTIFIER).at(0).UInt == 1684);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PLAYERCARINDEX).at(0).UInt == 0);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SECONDARYPLAYERCARINDEX).at(0).UInt == 255);
        test_assert(p.value(PacketEvent::EVENTSTRINGCODE).to_string() == "BUTN");
        test_assert(p.packets(PacketEvent::Buttons::BUTTONS).at(0)->value(PacketEvent::Buttons::BUTTONSTATUS).at(0).UInt == 4);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    try
    {
        unsigned int pos = 0;
        PacketCarStatus p(carstatuspacket, pos);

        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETFORMAT).at(0).UInt == 2021);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMAJORVERSION).at(0).UInt == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::GAMEMINORVERSION).at(0).UInt == 5);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETVERSION).at(0).UInt == 1);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PACKETID).at(0).UInt == 7);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONUID).at(0).UInt == 11396923571662120498U);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SESSIONTIME).at(0).Float == 11.7321501F);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::FRAMEIDENTIFIER).at(0).UInt == 240);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::PLAYERCARINDEX).at(0).UInt == 0);
        test_assert(p.packets(PacketHeader::PACKETHEADER).at(0)->value(PacketHeader::SECONDARYPLAYERCARINDEX).at(0).UInt == 255);

        // loop through number of participants making sure we don't throw.
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            unsigned int a; // stop warning
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::TRACTIONCONTROL).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ANTILOCKBRAKES).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELMIX).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FRONTBRAKEBIAS).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::PITLIMITERSTATUS).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELINTANK).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELCAPACITY).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::FUELREMAININGLAPS).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::MAXRPM).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::IDLERPM).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::MAXGEARS).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::DRSALLOWED).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::TYRESAGELAPS).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSSTOREENERGY).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSDEPLOYMODE).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP).at(0).UInt;
            a = p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(i)->value(PacketCarStatus::CarStatusData::NETWORKPAUSED).at(0).UInt;
        }

        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::TRACTIONCONTROL).at(0).UInt == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ANTILOCKBRAKES).at(0).UInt == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELMIX).at(0).UInt == 3);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FRONTBRAKEBIAS).at(0).UInt == 58);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::PITLIMITERSTATUS).at(0).UInt == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELINTANK).at(0).Float == 10);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELCAPACITY).at(0).Float == 110);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::FUELREMAININGLAPS).at(0).Float == 5.43956F);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::MAXRPM).at(0).UInt == 13000);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::IDLERPM).at(0).UInt == 3499);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::MAXGEARS).at(0).UInt == 9);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::DRSALLOWED).at(0).UInt == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE).at(0).UInt == 144);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND).at(0).UInt == 17);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND).at(0).UInt == 16);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::TYRESAGELAPS).at(0).UInt == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS).at(0).SInt == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSSTOREENERGY).at(0).Float == 4e+06F);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSDEPLOYMODE).at(0).UInt == 2);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK).at(0).Float == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH).at(0).Float == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP).at(0).Float == 0);
        test_assert(p.packets(PacketCarStatus::CarStatusData::CARSTATUSDATA).at(0)->value(PacketCarStatus::CarStatusData::NETWORKPAUSED).at(0).UInt == 0);
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
    }

    return 0;
}
