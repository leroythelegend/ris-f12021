#include "../inc/decoder1byte.h"

namespace ris
{
    Element Decoder1Byte::decode(const Bytes &bytes, Pos &pos)
    {
        Element result;
        result.Float = convertUIntToFloat(bytes.at(pos));
        result.UInt = bytes.at(pos);

        int8_t val = bytes.at(pos);
        result.SInt = val;

        pos += 1;

        return result;
    }

} // namespace ris
