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

    Values DecoderUInt16::decode(const Bytes &bytes, Pos &pos, const Amount &amount)
    {
        Values result;
        for (int i = 0; i < amount; ++i)
        {
            result.push_back(DecoderUInt16::decode(bytes, pos));
        }
        return result;
    }
} // namespace ris
