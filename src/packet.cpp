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

    std::map<Element, Values> Packet::telemetry() const
    {
        return telemetry_;
    }

    std::vector<Packet::Ptr> Packet::packets(const Element &element) const
    {
        map<Element, std::vector<Packet::Ptr>>::const_iterator it = packets_.find(element);
        if (it == packets_.end())
        {
            throw runtime_error("Unknown Packet " + element.to_string());
        }

        return it->second;
    }

    std::map<Element, std::vector<Packet::Ptr>> Packet::packets() const
    {
        return packets_;
    }

    void Packet::add(const Element &element, const std::vector<Packet::Ptr> &packets)
    {
        packets_.insert(std::pair<Element, std::vector<Packet::Ptr>>(element, packets));
    }

} // namespace ris
