#include "../inc/decoderuint8.h"

namespace ris
{
    double DecoderUInt8::decode(const Bytes &bytes, Pos &pos)
    {
        double result = static_cast<uint8_t>(bytes.at(pos));
        pos += 1;
        return result;
    }

    Values DecoderUInt8::decode(const Bytes &bytes, Pos &pos, const Amount &amount)
    {
        Values result;
        for (int i = 0; i < amount; ++i)
        {
            result.push_back(DecoderUInt8::decode(bytes, pos));
        }
        return result;
    }

} // namespace ris
