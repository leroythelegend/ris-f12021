#include "../inc/decoder8bytes.h"

namespace ris
{
    void Decoder8Bytes::decode(const Bytes &bytes, Pos &pos)
    {
        element_.Float = getFloatFromBytes(bytes, pos);
        element_.UInt = getUIntFromBytes(bytes, pos);
        element_.SInt = getSIntFromBytes(bytes, pos);

        pos += 8;
    }

    float Decoder8Bytes::getFloatFromBytes(const Bytes &bytes, Pos &pos)
    {
        return 0; // Float is only 4 bytes
    }

    uint64_t Decoder8Bytes::getUIntFromBytes(const Bytes &bytes, Pos &pos)
    {
        return static_cast<uint64_t>(bytes.at(pos + 7)) << 56 |
               static_cast<uint64_t>(bytes.at(pos + 6)) << 48 |
               static_cast<uint64_t>(bytes.at(pos + 5)) << 40 |
               static_cast<uint64_t>(bytes.at(pos + 4)) << 32 |
               static_cast<uint64_t>(bytes.at(pos + 3)) << 24 |
               static_cast<uint64_t>(bytes.at(pos + 2)) << 16 |
               static_cast<uint64_t>(bytes.at(pos + 1)) << 8 |
               bytes.at(pos);
    }

    int64_t Decoder8Bytes::getSIntFromBytes(const Bytes &bytes, Pos &pos)
    {
        return static_cast<int64_t>(bytes.at(pos + 7)) << 56 |
               static_cast<int64_t>(bytes.at(pos + 6)) << 48 |
               static_cast<int64_t>(bytes.at(pos + 5)) << 40 |
               static_cast<int64_t>(bytes.at(pos + 4)) << 32 |
               static_cast<int64_t>(bytes.at(pos + 3)) << 24 |
               static_cast<int64_t>(bytes.at(pos + 2)) << 16 |
               static_cast<int64_t>(bytes.at(pos + 1)) << 8 |
               bytes.at(pos);
    }

} // namespace ris
