#include "../inc/packet.h"

#include <stdexcept>
#include <string>

using namespace std;

namespace ris
{

    Values SubPacket::telemetry(const Element &element) const
    {
        TelemetryMap::const_iterator it = telemetry_.find(element);
        if (it == telemetry_.end())
        {
            throw runtime_error("Unknown Unit " + element.to_string());
        }

        return it->second;
    }

    SubPacket::TelemetryMap SubPacket::telemetry() const
    {
        return telemetry_;
    }

    Packet::SubPackets Packet::packets(const Element &element) const
    {
        PacketMap::const_iterator it = packets_.find(element);
        if (it == packets_.end())
        {
            throw runtime_error("Unknown Packet " + element.to_string());
        }

        return it->second;
    }

    Packet::PacketMap Packet::packets() const
    {
        return packets_;
    }

    void Packet::add(const Element &element, const SubPackets &packets)
    {
        packets_.insert(std::pair<Element, SubPackets>(element, packets));
    }

} // namespace ris
