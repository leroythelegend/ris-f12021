#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder2bytes.h"
#include "../inc/decoder4bytes.h"
#include "../inc/decoder8bytes.h"


namespace ris
{
    PacketHeader::PacketHeader(const Bytes &bytes, Pos &pos)
    {
        Decoder1Byte done;
        Decoder2Bytes dtwo;
        Decoder4Bytes dfour;
        Decoder8Bytes deight;

        done.decode(bytes, pos);
        telemetry_.insert(std::pair<Unit, Element>(1, done.decode(bytes, pos)));
    }
} // namespace ris
