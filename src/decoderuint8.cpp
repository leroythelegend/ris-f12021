#include "../inc/decoderuint8.h"

namespace ris
{
    void DecoderUInt8::decode(const Bytes &bytes, Pos &pos)
    {
        uint_ = bytes.at(pos);
        pos++;
    }

} // namespace ris
