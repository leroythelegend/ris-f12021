#include "../inc/packet.h"

#include <stdexcept>
#include <string>

using namespace std;

namespace ris
{

    Values Packet::value(const Element &element) const
    {
        map<Element, Values>::const_iterator it = telemetry_.find(element);
        if (it == telemetry_.end())
        {
            throw runtime_error("Unknown Unit " + element.to_string());
        }

        return it->second;
    }

    void Packet::add(const Packet::Ptr &packet)
    {
        packets_.push_back(packet);
    }

} // namespace ris
