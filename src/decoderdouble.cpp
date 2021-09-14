#include "../inc/decoderdouble.h"

namespace ris
{
    double DecoderDouble::decode(const Bytes &bytes, Pos &pos)
    {
        uint32_t val = (bytes.at(pos + 3) << 24) |
                       (bytes.at(pos + 2) << 16) |
                       (bytes.at(pos + 1) << 8) |
                       (bytes.at(pos));

        pos += 4;
        return val;
    }

    Values DecoderDouble::decode(const Bytes &bytes, Pos &pos, const Amount &amount)
    {
        Values result;
        for (int i = 0; i < amount; ++i)
        {
            result.push_back(DecoderDouble::decode(bytes, pos));
        }
        return result;
    }

} // namespace ris
