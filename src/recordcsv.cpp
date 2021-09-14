#include "../inc/recordcsv.h"
#include "../inc/csv.h"

#include <thread>
#include <iostream>

namespace ris
{
    void RecordCSV::record(Telemetries &telemetries)
    {
        if (telemetries->size())
        {
            std::thread t(
                [](Telemetries telemetries_)
                {
                    try
                    {

                        CSV::FileName filename("lap" + std::to_string(static_cast<unsigned int>(telemetries_->at(0).currentlap)) + ".csv");
                        CSV csv(filename);
                        csv.write(telemetries_);
                        telemetries_->clear();
                    }
                    catch (const std::exception &e)
                    {
                        std::cout << e.what() << '\n';
                    }
                },
                std::move(telemetries));
            t.detach();
        }
        telemetries = std::make_unique<std::vector<Telemetry>>();
    }
} // namespace ris
