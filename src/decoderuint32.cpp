#include "../inc/decoderuint32.h"

namespace ris
{
    void DecoderUInt32::decode(const Bytes &bytes, Pos &pos)
    {
        uint_ = (bytes.at(pos + 3) << 24) |
                (bytes.at(pos + 2) << 16) |
                (bytes.at(pos + 1) << 8) | 
                (bytes.at(pos));
        pos += 4;
    }

} // namespace ris
