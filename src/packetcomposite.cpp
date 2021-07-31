#include "../inc/packetcomposite.h"

#include <string>
#include <stdexcept>

namespace ris
{
    Values PacketComposite::value(const Element &element) const
    {
        for (auto packet : packets_)
        {
            try
            {
                return packet->value(element);
            }
            catch (const std::exception &e)
            {
                // continue until we find the unit
            }
        }
        // if we get here we did not find the unit
        throw std::runtime_error("Unknown Unit " + element.to_string());
    }
} // namespace ris
