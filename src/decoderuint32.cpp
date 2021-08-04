#include "../inc/decoderuint32.h"

namespace ris
{
    double DecoderUInt32::decode(const Bytes &bytes, Pos &pos)
    {
        uint32_t result = (bytes.at(pos + 3) << 24) |
                          (bytes.at(pos + 2) << 16) |
                          (bytes.at(pos + 1) << 8) |
                          (bytes.at(pos));
        pos += 4;
        return result;
    }

} // namespace ris
