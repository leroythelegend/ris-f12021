#include "../inc/decoderuint16.h"

namespace ris
{
    double DecoderUInt16::decode(const Bytes &bytes, Pos &pos)
    {
        uint16_t result = ((bytes.at(pos + 1) << 8) |
                          (bytes.at(pos)));

        pos += 2;

        return result;
    }
} // namespace ris
