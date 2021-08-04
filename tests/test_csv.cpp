#include <iostream>
#include <string>
#include <fstream>

#include "../inc/packetheader.h"
#include "../inc/packetcartelemetrydata.h"
#include "../inc/networkfile.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{
    Bytes cartelemetrypacket;

    try
    {
        NetworkFile t("../tests/vectors/car_telemetry.bin");
        cartelemetrypacket = t.read();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        ofstream o("/tmp/test.csv");

        vector<Packet::Ptr> p;
        p.push_back(make_shared<PacketCarTelemetryData>(cartelemetrypacket));
        p.push_back(make_shared<PacketCarTelemetryData>(cartelemetrypacket));
        p.push_back(make_shared<PacketCarTelemetryData>(cartelemetrypacket));
        p.push_back(make_shared<PacketCarTelemetryData>(cartelemetrypacket));
        p.push_back(make_shared<PacketCarTelemetryData>(cartelemetrypacket));

        vector<string> headers;
        vector<vector<string>> values;

        bool haveHeaders = false;
        for (auto ps : p)
        {
            if (!haveHeaders)
            {
                for (auto const &[key, val] : ps->packets())
                {
                    if (key.to_string() != PacketHeader::PACKETHEADER.to_string())
                    {
                        for (auto const &[name, element] : val.at(0)->telemetry())
                        {
                            if (element.size() == 1)
                            {
                                for (auto _ : element)
                                {
                                    headers.push_back(name.to_string());
                                }
                            }
                            else
                            {
                                for (unsigned int i = 1; i <= element.size(); ++i)
                                {
                                    headers.push_back(name.to_string() + "_" + to_string(i));
                                }
                            }
                        }
                    }
                }
                haveHeaders = true;
            }

            vector<string> row;
            for (auto packet : ps->packets())
            {
                if (packet.first.to_string() != PacketHeader::PACKETHEADER.to_string())
                {
                    for (auto telemetry : packet.second.at(static_cast<size_t>(ps->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)))->telemetry())
                    {
                        for (unsigned int i = 0; i < telemetry.second.size(); ++i)
                        {
                            row.push_back(to_string(telemetry.second.at(i)));
                        }
                    }
                }
            }
            values.push_back(row);
            row.clear();
        }

        string str;
        for (auto h : headers)
        {
            str += h + ",";
        }
        str.pop_back();
        o << str << endl;
        str.clear();
        for (auto v : values)
        {
            for (auto r : v)
            {
                str += r + ",";
            }
            str.pop_back();
            o << str << endl;
            str.clear();
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
