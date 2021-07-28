#include "../inc/decoder.h"

namespace ris
{
    float Decoder::convertUIntToFloat(const uint32_t i) const
    {
        union
        {
            uint32_t val;
            float f;
        } u = {i};

        return u.f;
    }
} // namespace ris
