#include "../inc/packet.h"

namespace ris
{
    void Packet::decode(const Bytes &bytes, Pos &pos)
    {
        for (auto decoder : decoders_)
        {
            decoder->decode(bytes, pos);
        }
    }
} // namespace ris
