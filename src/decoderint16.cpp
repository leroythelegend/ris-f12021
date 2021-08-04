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
} // namespace ris
