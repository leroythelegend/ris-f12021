#include "../inc/decoderint16.h"

namespace ris
{
    double DecoderInt16::decode(const Bytes &bytes, Pos &pos)
    {
        int16_t result = ((bytes.at(pos + 1) << 8) |
                          (bytes.at(pos)));

        pos += 2;

        return result;
    }

    Values DecoderInt16::decode(const Bytes &bytes, Pos &pos, const Amount &amount)
    {
        Values result;
        for (int i = 0; i < amount; ++i)
        {
            result.push_back(DecoderInt16::decode(bytes, pos));
        }
        return result;
    }
} // namespace ris
