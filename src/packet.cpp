#include "../inc/packet.h"

#include <stdexcept>
#include <string>

using namespace std;

namespace ris
{

    Element Packet::element(const Unit &unit) const
    {
        map<Unit, Element>::const_iterator it = telemetry_.find(unit);
        if (it == telemetry_.end())
        {
            throw runtime_error("Unknown Unit " + to_string(unit));
        }

        return it->second;
    }

} // namespace ris
