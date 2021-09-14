#include "../inc/decoderuint8.h"

namespace ris
{
    double DecoderUInt8::decode(const Bytes &bytes, Pos &pos)
    {
        return static_cast<uint8_t>(bytes.at(pos++));
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
