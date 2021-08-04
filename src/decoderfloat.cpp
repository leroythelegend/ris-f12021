#include "../inc/decoderfloat.h"

namespace ris
{
    double DecoderFloat::decode(const Bytes &bytes, Pos &pos)
    {
        uint32_t val = (bytes.at(pos + 3) << 24) |
                       (bytes.at(pos + 2) << 16) |
                       (bytes.at(pos + 1) << 8) |
                       (bytes.at(pos));
        union
        {
            uint32_t val;
            float f;
        } u = {val};

        double result = u.f;
        pos += 4;
        return result;
    }

} // namespace ris
