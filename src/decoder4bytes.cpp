#include "../inc/decoder4bytes.h"

namespace ris
{
    void Decoder4Bytes::decode(const Bytes &bytes, Pos &pos)
    {
        element_.Float = getFloatFromBytes(bytes, pos);
        element_.UInt = getUIntFromBytes(bytes, pos);
        element_.SInt = getSIntFromBytes(bytes, pos);

        pos += 4;
    }

    float Decoder4Bytes::getFloatFromBytes(const Bytes &bytes, Pos &pos)
    {
        uint32_t val = (bytes.at(pos + 3) << 24) |
                       (bytes.at(pos + 2) << 16) |
                       (bytes.at(pos + 1) << 8) |
                       (bytes.at(pos));
        return convertUIntToFloat(val);
    }
    
    uint64_t Decoder4Bytes::getUIntFromBytes(const Bytes &bytes, Pos &pos)
    {
        return (bytes.at(pos + 3) << 24) |
               (bytes.at(pos + 2) << 16) |
               (bytes.at(pos + 1) << 8) |
               (bytes.at(pos));
    }
        
    int64_t Decoder4Bytes::getSIntFromBytes(const Bytes &bytes, Pos &pos)
    {
        int32_t result = (bytes.at(pos + 3) << 24) |
                         (bytes.at(pos + 2) << 16) |
                         (bytes.at(pos + 1) << 8) |
                         (bytes.at(pos));
        return result;
    }

} // namespace ris
