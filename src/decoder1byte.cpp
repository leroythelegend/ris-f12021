#include "../inc/decoder1byte.h"

namespace ris
{
    void Decoder1Byte::decode(const Bytes &bytes, Pos &pos)
    {
        element_.Float = convertUIntToFloat(bytes.at(pos));
        element_.UInt = bytes.at(pos);

        int8_t val = bytes.at(pos);
        element_.SInt = val;

        pos += 1;
    }

} // namespace ris
