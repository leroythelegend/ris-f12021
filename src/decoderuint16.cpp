#include "../inc/decoderuint16.h"

namespace ris
{
    void DecoderUInt16::decode(const Bytes &bytes, Pos &pos)
    {
        Decoder::uint_ = ((bytes.at(pos + 1) << 8) | (bytes.at(pos)));
        pos += 2;
    }

} // namespace ris
