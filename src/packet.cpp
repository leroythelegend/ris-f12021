#include "../inc/packet.h"

namespace ris
{

    Element Packet::element(const Unit &unit) const
    {
        std::map<Unit, Element>::const_iterator it = telemetry_.find(unit);
        if (it != telemetry_.end())
        {
            throw std::runtime_error("Unknown Unit " + std::to_string(unit));
        }

        return it->second;
    }

} // namespace ris
