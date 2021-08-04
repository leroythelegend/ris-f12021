#include "../inc/decoderint8.h"

namespace ris
{
    double DecoderInt8::decode(const Bytes &bytes, Pos &pos)
    {
        double result = static_cast<int8_t>(bytes.at(pos));
        pos += 1;
        return result;
    }

    Values DecoderInt8::decode(const Bytes &bytes, Pos &pos, const Amount &amount)
    {
        Values result;
        for (int i = 0; i < amount; ++i)
        {
            result.push_back(DecoderInt8::decode(bytes, pos));
        }
        return result;
    }

} // namespace ris
