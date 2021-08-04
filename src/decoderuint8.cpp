#include "../inc/decoderuint8.h"

namespace ris
{
    double DecoderUInt8::decode(const Bytes &bytes, Pos &pos)
    {
        double result = static_cast<uint8_t>(bytes.at(pos));
        pos += 1;
        return result;
    }

} // namespace ris
