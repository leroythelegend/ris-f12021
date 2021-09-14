#include "../inc/networkudp.h"
#include "../inc/packetheader.h"
#include "../inc/packetevent.h"
#include "../inc/packetlapdata.h"
#include "../inc/packetcartelemetrydata.h"
#include "../inc/telemetry.h"
#include "../inc/csv.h"
#include "../inc/capturecsv.h"
#include "../inc/processcartelemetry.h"
#include "../inc/recordcsv.h"

#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include <memory>

using namespace std;
using namespace ris;

// class Process
// {
// public:
//     using Ptr = shared_ptr<Process>;
//     using Packets = std::shared_ptr<std::vector<Bytes>>;

//     virtual ~Process() = default;

//     virtual Telemetry getTelemetry(const Packets &packets) = 0;
//     virtual void processLapTelemetry(Telemetries &, const double) = 0;
// };

// class ProcessCarTelemetry : public Process
// {
// public:
//     virtual ~ProcessCarTelemetry() = default;

//     Telemetry getTelemetry(const Packets &packets) override
//     {
//         Telemetry telemetry;

//         for (auto b : *packets)
//         {
//             if ((PacketID)b.at(5) == PacketID::Car_Telemetry)
//             {
//                 PacketCarTelemetryData packet(b);
//                 telemetry.packets.push_back(packet.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(packet.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)));
//                 telemetry.packets.push_back(packet.packets(PacketCarTelemetryData::CarTelemetryData::CARTELEMETRYDATA).at(0));
//                 break;
//             }
//         }

//         return telemetry;
//     }

//     void processLapTelemetry(Telemetries &telemetries, const double currentlap) override
//     {
//         if (telemetries.size())
//         {
//             CSV::FileName filename("lap" + to_string(static_cast<unsigned int>(currentlap)) + ".csv");
//             CSV csv(filename);
//             csv.write(telemetries);
//             telemetries.clear();
//         }
//     }
// };


// class Capture
// {
// public:
//     using Packets = std::shared_ptr<std::vector<Bytes>>;

//     Capture(unsigned int port, Process::Ptr process)
//         : network_{port},
//           process_{process}
//     {
//     }

//     void start()
//     {
//         while (true)
//         {
//             Packets packets = getAllPacketsFromFrame();

//             if (packets && !packets->empty())
//             {
//                 PacketLapData::Ptr lapdata = getLapDataPacket(packets);

//                 if (lapdata)
//                 {
//                     double playerindex = getPlayerIndex(lapdata);

//                     if (hasLapStarted(lapdata))
//                     {
//                         // start recording
//                         if (currentlap_ != lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0))
//                         {
//                             processLapTelemetry();
//                             updateCurrentLap(lapdata);
//                             displayLapInfo();
//                         }
//                         else
//                         {
//                             if (!startedrecording_)
//                             {
//                                 startedrecording_ = true;
//                                 displayLapInfo();
//                             }
//                             updateLapTelemetry(lapdata, packets);
//                         }
//                     }
//                     else if (lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::PITSTATUS).at(0) == 1)
//                     {
//                         resetValues();
//                     }
//                     else
//                     {
//                         updateCurrentLap(lapdata);
//                     }
//                 }
//                 packets->clear();
//             }
//         }
//     }

// private:
//     Packets getAllPacketsFromFrame()
//     {
//         Packets result;
//         while (true)
//         {
//             ris::Bytes bytes = network_.read();

//             if (isSessionOver(bytes))
//             {
//                 return nullptr;
//             }

//             Pos pos = 0;
//             PacketHeader header(bytes, pos);

//             double nextframe = header.telemetry(PacketHeader::FRAMEIDENTIFIER).at(0);

//             if (frame_ == nextframe)
//             {
//                 nextpackets_->push_back(bytes);
//                 continue;
//             }
//             else if (frame_ == 0 || nextframe == 0)
//             {
//                 frame_ = nextframe;
//                 continue;
//             }
//             else if (nextframe >= frame_)
//             {
//                 result = move(nextpackets_);

//                 nextpackets_ = make_shared<std::vector<Bytes>>();
//                 nextpackets_->push_back(bytes);
//                 frame_ = nextframe;
//                 return move(result);
//             }
//             else
//             {
//                 continue;
//             }
//         }
//     }

//     bool isSessionOver(const Bytes &bytes)
//     {
//         PacketID packetid = (PacketID)bytes.at(5);
//         if (packetid == PacketID::Event)
//         {
//             PacketEvent event(bytes);

//             if (event.packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() == "SEND")
//             {
//                 resetValues();
//                 return true;
//             }
//         }
//         return false;
//     }

//     void resetValues()
//     {
//         currentlap_ = 0;
//         telemetries_.clear();
//         frame_ = 0;
//         nextpackets_->clear();
//         nextlap_ = 0;
//         startedrecording_ = false;
//     }

//     PacketLapData::Ptr getLapDataPacket(const Packets &packets)
//     {
//         for (const auto &bytes : *packets)
//         {
//             if ((PacketID)bytes.at(5) == PacketID::Lap_Data)
//             {
//                 return make_shared<PacketLapData>(bytes);
//             }
//         }
//         return nullptr;
//     }

//     double getPlayerIndex(PacketLapData::Ptr lapdata)
//     {
//         return lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0);
//     }

//     bool hasLapStarted(PacketLapData::Ptr lapdata)
//     {
//         double playerindex = getPlayerIndex(lapdata);

//         return (lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0) >= 0 &&
//                 (lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0) != 0 ||
//                  lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0) < 50) &&
//                 currentlap_);
//     }

//     void processLapTelemetry()
//     {
//         process_->processLapTelemetry(telemetries_, currentlap_);
//     }

//     void updateLapTelemetry(PacketLapData::Ptr lapdata, Packets &packets)
//     {
//         Telemetry telemetry = process_->getTelemetry(packets);

//         if (!telemetry.packets.empty())
//         {
//             double playerindex = getPlayerIndex(lapdata);
//             telemetry.time = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0);
//             telemetry.distance = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0);
//             telemetries_.push_back(telemetry);
//         }
//     }

//     void updateCurrentLap(PacketLapData::Ptr lapdata)
//     {
//         currentlap_ = lapdata->packets(PacketLapData::LapData::LAPDATA).at(getPlayerIndex(lapdata))->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0);
//     }

//     void displayLapInfo()
//     {
//         cout << "recording lap " << currentlap_ << endl;
//     }

//     ris::NetworkUDP network_;
//     Process::Ptr process_;

//     Packets nextpackets_ = make_shared<std::vector<Bytes>>();

//     Telemetries telemetries_;
//     double currentlap_ = 0;
//     double nextlap_ = 0;
//     double frame_ = 0;
//     bool startedrecording_ = false;
// };

int main(int argc, char const *argv[])
{

    try
    {
        ris::CaptureCSV capture(20777, std::make_shared<ProcessCarTelemetry>(std::make_shared<RecordCSV>()));

        capture.start();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    // try
    // {
    //     Capture capture(20777, make_shared<ProcessCarTelemetry>());

    //     capture.start();
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << e.what() << '\n';
    //     return 1;
    // }

    // try
    // {
    //     ris::NetworkUDP network(20777);
    //     double frame = 0;

    //     shared_ptr<std::vector<Bytes>> nextpackets = make_shared<std::vector<Bytes>>();
    //     shared_ptr<std::vector<Bytes>> packets;

    //     double currentlap = 0;
    //     double nextlap = 0;
    //     Telemetries telemetries;
    //     // unsigned int skipfirst10packets = 10;

    //     while (true)
    //     {
    //         // need to start to record a lap

    //         // What I'm going to need
    //         // - header
    //         //   - check version nore sure if I need to check minor verion or major version
    //         //   - session time stamp from the header
    //         //   - frame id from header
    //         //   - player index from header
    //         // - session packet
    //         //   - track id
    //         //   - formula
    //         //   - weather info
    //         // - lap data
    //         //   - lap distance
    //         //   - last lap time in ms
    //         //   - current time in ms
    //         //   - current lap number!!!!!

    //         // Frame one
    //         //     • Session
    //         //     • Participants
    //         //     • Car Setups
    //         //     • Lap Data
    //         //     • Motion Data
    //         //     • Car Telemetry
    //         //     • Car Status
    //         //     • Car Damage

    //         // Frame two
    //         //      • Lap Data
    //         //      • Motion Data
    //         //      • Car Telemetry
    //         //      • Car Status

    //         // Frame Thirty one
    //         //      • Session (since 2 updates per second)
    //         //      • Car Setups (since 2 updates per second)
    //         //      • Lap Data
    //         //      • Motion Data
    //         //      • Car Telemetry
    //         //      • Car Status
    //         //      • Car Damage (since 2 updates per second)

    //         // CSV files
    //         // - motion data
    //         // - weather
    //         // - telemetry
    //         //

    //         // Get all the packets for the frame.
    //         // decode lap data packet
    //         ris::Bytes bytes = network.read();

    //         Pos pos = 0;
    //         PacketHeader header(bytes, pos);

    //         // get events SEND (session end) and SSTA (session started)
    //         PacketID packetid = (PacketID)bytes.at(5);
    //         if (packetid == PacketID::Event)
    //         {
    //             PacketEvent event(bytes);

    //             if (event.packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() == "SEND")
    //             {
    //                 cout << event.packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() << endl;
    //                 currentlap = 0;
    //                 telemetries.clear();
    //                 frame = 0;
    //                 nextpackets->clear();
    //                 packets->clear();
    //                 nextlap = 0;
    //             }
    //         }

    //         // cout << bytes.size() << endl;

    //         // cout << "session time " << header.telemetry(PacketHeader::SESSIONTIME).at(0) << endl;
    //         // cout << "frame " << header.telemetry(PacketHeader::FRAMEIDENTIFIER).at(0) << endl;

    //         ////// this where I'm upto
    //         double nextframe = header.telemetry(PacketHeader::FRAMEIDENTIFIER).at(0);

    //         if (frame == nextframe)
    //         {
    //             nextpackets->push_back(bytes);
    //             continue;
    //         }
    //         else if (frame == 0 || nextframe == 0)
    //         {
    //             frame = nextframe;
    //             continue;
    //         }
    //         else if (nextframe >= frame)
    //         {
    //             packets = move(nextpackets);

    //             nextpackets = make_shared<std::vector<Bytes>>();
    //             nextpackets->push_back(bytes);
    //             frame = nextframe;
    //         }
    //         else
    //         {
    //             continue;
    //         }

    //         if (!packets->empty())
    //         {
    //             shared_ptr<PacketLapData> lapdata;
    //             for (auto b : *packets)
    //             {
    //                 // std::cout << (unsigned int)b.at(5) << std::endl;
    //                 // find lap data packet
    //                 if ((PacketID)b.at(5) == PacketID::Lap_Data)
    //                 {
    //                     lapdata = make_shared<PacketLapData>(b);
    //                     break;
    //                 }
    //             }

    //             if (lapdata)
    //             {
    //                 double playerindex = lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0);

    //                 cout << lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0) << endl;

    //                 if (lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0) >= 0 &&
    //                     (lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0) != 0 ||
    //                      lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0) < 500) &&
    //                     currentlap)
    //                 {
    //                     // start recording
    //                     if (currentlap != lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0))
    //                     {
    //                         if (telemetries.size())
    //                         {
    //                             CSV::FileName filename("lap" + to_string(static_cast<unsigned int>(currentlap)) + ".csv");
    //                             CSV csv(filename);
    //                             csv.write(telemetries);
    //                             telemetries.clear();
    //                         }
    //                         currentlap = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0);
    //                     }
    //                     else
    //                     {
    //                         cout << "recording " << currentlap << endl;

    //                         Telemetry telemetry;

    //                         for (auto b : *packets)
    //                         {
    //                             // std::cout << (unsigned int)b.at(5) << std::endl;
    //                             // find lap data packet

    //                             if ((PacketID)b.at(5) == PacketID::Car_Telemetry)
    //                             {
    //                                 PacketCarTelemetryData packet(b);
    //                                 telemetry.packets.push_back(packet.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(playerindex));
    //                                 telemetry.packets.push_back(packet.packets(PacketCarTelemetryData::CarTelemetryData::CARTELEMETRYDATA).at(0));
    //                                 break;
    //                             }
    //                         }

    //                         if (!telemetry.packets.empty())
    //                         {
    //                             telemetry.time = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0);
    //                             telemetry.distance = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0);
    //                             telemetries.push_back(telemetry);
    //                         }
    //                     }
    //                 }
    //                 else if (lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::PITSTATUS).at(0) == 1)
    //                 {
    //                     currentlap = 0;
    //                     telemetries.clear();
    //                     frame = 0;
    //                     nextpackets->clear();
    //                     packets->clear();
    //                     nextlap = 0;
    //                 }
    //                 else
    //                 {
    //                     currentlap = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0);
    //                 }
    //             }
    //             // std::cout << std::endl;
    //             packets->clear();
    //         }
    //         ///////

    // // get packet id
    // PacketID packetid = (PacketID)bytes.at(5);

    // // strange I have to track frame
    // Pos pos = 0;
    // PacketHeader header(bytes, pos);

    // double thisframe = header.telemetry(PacketHeader::FRAMEIDENTIFIER).at(0);
    // if (frame == 0 || thisframe == 0 || thisframe >= frame)
    // {
    //     frame = thisframe;
    //     // get all the packets for that frame

    // }
    // else
    // {
    //     continue;
    // }

    // cout << "packet id " << (unsigned int)packetid << " frame " << frame << endl;

    // if (packetid == PacketID::Lap_Data)
    // {
    //     PacketLapData lapdata(bytes);

    //     double playerindex = lapdata.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0);

    //     if (lapdata.packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0) >= 0)
    //     {
    //         // std::cout << "record lap number " << lapdata.packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0) << endl;
    //         // std::cout << "vaild lap " << lapdata.packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPINVALID).at(0) << endl;
    //         // std::cout << "time " << lapdata.packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0)
    //         //           << " dis " << lapdata.packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0)
    //         //           << " index " << playerindex
    //         //           << " frame " << lapdata.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::FRAMEIDENTIFIER).at(0) << endl;
    //     }
    // }

    // // Still missing some packets that need testing
    // unsigned int packetid = (unsigned int)bytes.at(5);

    // if (packetid == (unsigned int)PacketID::Final_Classification ||
    //     packetid == (unsigned int)PacketID::Lobby_Info
    //     )
    // {
    //     ofstream outfile("/tmp/f12021.out", ios::out | ios::binary);
    //     cout << "not event captured size " << bytes.size() << endl;
    //     outfile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
    //     return 1;
    // }
    // else if (packetid == (unsigned)PacketID::Event)
    // {
    //     if (PacketEvent(bytes).packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() != "BUTN" &&
    //         PacketEvent(bytes).packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() != "SPTP")
    //     {
    //         ofstream outfile("/tmp/event.out", ios::out | ios::binary);
    //         cout << "event captured size " << bytes.size() << " " << PacketEvent(bytes).packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() << endl;
    //         outfile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());
    //         return 1;
    //     }
    // }
    //     }
    // }
    // catch (std::exception &e)
    // {
    //     cout << "ERROR " << e.what() << endl;
    // }
    // catch (...)
    // {
    //     cout << "no idea" << endl;
    // }
    return 0;
}
