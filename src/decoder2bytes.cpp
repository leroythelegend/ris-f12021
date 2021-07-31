#include "../inc/decoder2bytes.h"

namespace ris
{
    Value Decoder2Bytes::decode(const Bytes &bytes, Pos &pos)
    {
        Value result;
        result.Float = getFloatFromBytes(bytes, pos);
        result.UInt = getUIntFromBytes(bytes, pos);
        result.SInt = getSIntFromBytes(bytes, pos);

        pos += 2;

        return result;
    }

    float Decoder2Bytes::getFloatFromBytes(const Bytes &bytes, Pos &pos)
    {
        uint32_t val = ((bytes.at(pos + 1) << 8) |
                        (bytes.at(pos)));
        return convertUIntToFloat(val);
    }

    uint64_t Decoder2Bytes::getUIntFromBytes(const Bytes &bytes, Pos &pos)
    {
        return ((bytes.at(pos + 1) << 8) |
                (bytes.at(pos)));
    }

    int64_t Decoder2Bytes::getSIntFromBytes(const Bytes &bytes, Pos &pos)
    {
        int16_t result = ((bytes.at(pos + 1) << 8) |
                          (bytes.at(pos)));
        return result;
    }

} // namespace ris
