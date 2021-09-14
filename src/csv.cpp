#include "../inc/csv.h"

#include "../inc/packetheader.h"

#include <iostream>

namespace ris
{
    CSV::CSV(const FileName &filename)
        : network{filename} {}

    void CSV::write(const Telemetries &telemetries) const
    {
        if (telemetries->empty())
        {
            return;
        }

        // write the header
        std::string header;
        header.append("TIMESTAMP,");
        header.append("DISTANCE,");

        for (const auto &p : telemetries->at(0).packets)
        {
            for (auto t : p->telemetry())
            {
                int index = 1;
                for (auto v : t.second)
                {
                    header.append(t.first.to_string());
                    if (t.second.size() > 1)
                    {
                        header.append(std::to_string(index++));
                    }
                    header.append(",");
                }
            }
        }
        header.pop_back(); // remove comma
        header.append("\r\n");

        // write the data
        // std::string data;
        for (const auto &telemetry : *telemetries)
        {
            header.append(std::to_string(telemetry.time));
            header.append(",");
            header.append(std::to_string(telemetry.distance));
            header.append(",");
            for (auto p : telemetry.packets)
            {
                for (auto t : p->telemetry())
                {
                    for (auto v : t.second)
                    {
                        header.append(std::to_string(v));
                        header.append(",");
                    }
                }
            }
            header.pop_back(); // remove comma
            header.append("\r\n");
        }
        network.write(header);
    }

} // namespace ris
