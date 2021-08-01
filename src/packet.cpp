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

    std::vector<Packet::Ptr> Packet::packets(const int i) const
    {
        map<int, std::vector<Packet::Ptr>>::const_iterator it = packets_.find(i);
        if (it == packets_.end())
        {
            throw runtime_error("Unknown Packet " + std::to_string(i));
        }

        return it->second;
    }

    void Packet::add(const int i, const std::vector<Packet::Ptr> &packets)
    {
        packets_.insert(std::pair<int, std::vector<Packet::Ptr>>(i, packets));
    }

} // namespace ris
