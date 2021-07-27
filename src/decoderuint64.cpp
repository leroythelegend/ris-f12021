#include "../inc/decoderuint64.h"

namespace ris
{
    void DecoderUInt64::decode(const Bytes &bytes, Pos &pos)
    {
        Decoder::uint_ = static_cast<uint64_t>(bytes.at(pos + 7)) << 56 |
                         static_cast<uint64_t>(bytes.at(pos + 6)) << 48 |
                         static_cast<uint64_t>(bytes.at(pos + 5)) << 40 |
                         static_cast<uint64_t>(bytes.at(pos + 4)) << 32 |
                         static_cast<uint64_t>(bytes.at(pos + 3)) << 24 |
                         static_cast<uint64_t>(bytes.at(pos + 2)) << 16 |
                         static_cast<uint64_t>(bytes.at(pos + 1)) << 8  |
                         bytes.at(pos);
        pos += 8;
    }

} // namespace ris
