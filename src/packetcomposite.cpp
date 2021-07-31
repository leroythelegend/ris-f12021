#include "../inc/packetcomposite.h"

#include <string>
#include <stdexcept>

namespace ris
{
    Elements PacketComposite::element(const Unit &unit) const
    {
        for (auto packet : packets_)
        {
            try
            {
                return packet->element(unit);
            }
            catch(const std::exception& e)
            {
                // continue until we find the unit
            }
        }
        // if we get here we did not find the unit
        throw std::runtime_error("Unknown Unit " + std::to_string(unit));
    }
} // namespace ris
