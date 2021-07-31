#include "../inc/packetevent.h"
#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder2bytes.h"
#include "../inc/decoder4bytes.h"
#include "../inc/decoder8bytes.h"


namespace ris
{
    PacketEvent::PacketEvent(const Bytes &bytes, Pos &pos)
    {
        Packet::add(std::make_shared<PacketHeader>(bytes, pos));

        // Decoder1Byte decoderonebyte;
        // Decoder2Bytes decodertwobytes;
        // Decoder4Bytes decoderfourbytes;
        // Decoder8Bytes decodereightbytes;

        // telemetry_.insert(std::pair<Unit, Element>(1, decodertwobytes.decode(bytes, pos)));
        // telemetry_.insert(std::pair<Unit, Element>(2, decoderonebyte.decode(bytes, pos)));
        // telemetry_.insert(std::pair<Unit, Element>(3, decoderonebyte.decode(bytes, pos)));
        // telemetry_.insert(std::pair<Unit, Element>(4, decoderonebyte.decode(bytes, pos)));
        // telemetry_.insert(std::pair<Unit, Element>(5, decoderonebyte.decode(bytes, pos)));
        // telemetry_.insert(std::pair<Unit, Element>(6, decodereightbytes.decode(bytes, pos)));
        // telemetry_.insert(std::pair<Unit, Element>(7, decoderfourbytes.decode(bytes, pos)));
        // telemetry_.insert(std::pair<Unit, Element>(8, decoderfourbytes.decode(bytes, pos)));
        // telemetry_.insert(std::pair<Unit, Element>(9, decoderonebyte.decode(bytes, pos)));
        // telemetry_.insert(std::pair<Unit, Element>(10, decoderonebyte.decode(bytes, pos)));
    }
} // namespace ris
