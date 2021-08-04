#include "../inc/decoderint8.h"

namespace ris
{
    double DecoderInt8::decode(const Bytes &bytes, Pos &pos)
    {
        double result = static_cast<int8_t>(bytes.at(pos));
        pos += 1;
        return result;
    }

} // namespace ris
