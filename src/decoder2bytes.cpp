#include "../inc/decoder2bytes.h"

namespace ris
{
    void Decoder2Bytes::decode(const Bytes &bytes, Pos &pos)
    {
        element_.Float = getFloatFromBytes(bytes, pos);
        element_.UInt = getUIntFromBytes(bytes, pos);
        element_.SInt = getSIntFromBytes(bytes, pos);

        pos += 2;
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
