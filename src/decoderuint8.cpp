#include "../inc/decoderuint8.h"

namespace ris
{
    void DecoderUInt8::decode(const Bytes &bytes, Pos &pos)
    {
        Decoder::uint_ = bytes.at(pos);
        pos++;
    }

} // namespace ris
