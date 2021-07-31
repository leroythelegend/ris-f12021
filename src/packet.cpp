#include "../inc/packet.h"

#include <stdexcept>
#include <string>

using namespace std;

namespace ris
{

    Values Packet::element(const Unit &unit) const
    {
        map<Unit, Values>::const_iterator it = telemetry_.find(unit);
        if (it == telemetry_.end())
        {
            throw runtime_error("Unknown Unit " + to_string(unit));
        }

        return it->second;
    }

    void Packet::add(const Packet::Ptr &packet)
    {
        packets_.push_back(packet);
    }

} // namespace ris
