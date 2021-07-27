#pragma once

#include <vector>

#include "../inc/packet.h"

#include "../inc/decoderfloat.h"
#include "../inc/decoderuint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderuint64.h"

namespace ris
{

    class PacketHeader : public Packet
    {
    public:
        PacketHeader();
        ~PacketHeader() = default;
    
        uint64_t packetFormat() const;
        uint64_t gameMajorVersion() const;
        uint64_t gameMinorVersion() const;
        uint64_t packetVersion() const;
        uint64_t packetID() const;
        uint64_t sessionUID() const;
        float sessionTime() const;
        uint64_t frameIdentifier() const;
        uint64_t playerCarIndex() const;
        uint64_t secondaryPlayerCarIndex() const;        

    private:
        Decoder::Ptr packetformat_ = std::make_shared<DecoderUInt16>();
        Decoder::Ptr gamemajorversion_ = std::make_shared<DecoderUInt8>();
        Decoder::Ptr gameminorversion_ = std::make_shared<DecoderUInt8>();
        Decoder::Ptr packetversion_ = std::make_shared<DecoderUInt8>();
        Decoder::Ptr packetid_ = std::make_shared<DecoderUInt8>();
        Decoder::Ptr sessionuid_ = std::make_shared<DecoderUInt64>();
        Decoder::Ptr sessiontime_ = std::make_shared<DecoderFloat>();
        Decoder::Ptr frameidentifier_ = std::make_shared<DecoderUInt32>();
        Decoder::Ptr playercarindex_ = std::make_shared<DecoderUInt8>();
        Decoder::Ptr secondaryplayercarindex_ = std::make_shared<DecoderUInt8>();
    };

} // namespace ris
