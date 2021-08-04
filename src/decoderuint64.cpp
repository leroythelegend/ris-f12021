#include "../inc/decoderuint64.h"

namespace ris
{
    double DecoderUInt64::decode(const Bytes &bytes, Pos &pos)
    {
        uint32_t lsb = static_cast<uint64_t>(bytes.at(pos + 3)) << 24 |
                       static_cast<uint64_t>(bytes.at(pos + 2)) << 16 |
                       static_cast<uint64_t>(bytes.at(pos + 1)) << 8 |
                       bytes.at(pos);

        pos += 4;

        uint32_t msb = static_cast<uint64_t>(bytes.at(pos + 3)) << 24 |
                       static_cast<uint64_t>(bytes.at(pos + 2)) << 16 |
                       static_cast<uint64_t>(bytes.at(pos + 1)) << 8 |
                       bytes.at(pos);

        pos += 4;

        return (lsb ^ msb);
    }

} // namespace ris
