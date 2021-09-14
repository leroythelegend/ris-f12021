#include "../inc/recordcsv.h"
#include "../inc/csv.h"

namespace ris
{
    void RecordCSV::record(Telemetries &telemetries)
    {
        if (telemetries.size())
        {
            CSV::FileName filename("lap" + std::to_string(static_cast<unsigned int>(telemetries.at(0).currentlap)) + ".csv");
            CSV csv(filename);
            csv.write(telemetries);
            telemetries.clear();
        }        
    }
} // namespace ris
