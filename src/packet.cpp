#include "../inc/packet.h"

namespace ris
{
    void Packet::decode(const Bytes &bytes)
    {
        unsigned int pos = 0;
        for (auto decoder : decoders_)
        {
            decoder->decode(bytes, pos);
        }
    }
} // namespace ris
