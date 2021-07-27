#include "../inc/packetheader.h"
#include "../inc/decoderfloat.h"
#include "../inc/decoderuint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderuint64.h"

namespace ris
{
    PacketHeader::PacketHeader()
    {
        decoders_.push_back(packetformat_);
        decoders_.push_back(gamemajorversion_);
        decoders_.push_back(gameminorversion_);
        decoders_.push_back(packetversion_);
        decoders_.push_back(packetid_);
        decoders_.push_back(sessionuid_);
        decoders_.push_back(sessiontime_);
        decoders_.push_back(frameidentifier_);
        decoders_.push_back(playercarindex_);
        decoders_.push_back(secondaryplayercarindex_);
    }

    uint64_t PacketHeader::packetFormat() const
    {
        return packetformat_->uint();
    }

    uint64_t PacketHeader::gameMajorVersion() const
    {
        return gamemajorversion_->uint();
    }

    uint64_t PacketHeader::gameMinorVersion() const
    {
        return gameminorversion_->uint();
    }

    uint64_t PacketHeader::packetVersion() const
    {
        return packetversion_->uint();
    }

    uint64_t PacketHeader::packetID() const
    {
        return packetid_->uint();
    }

    uint64_t PacketHeader::sessionUID() const
    {
        return sessionuid_->uint();
    }

    float PacketHeader::sessionTime() const
    {
        return sessiontime_->float32();
    }

    uint64_t PacketHeader::frameIdentifier() const
    {
        return frameidentifier_->uint();
    }

    uint64_t PacketHeader::playerCarIndex() const
    {
        return playercarindex_->uint();
    }

    uint64_t PacketHeader::secondaryPlayerCarIndex() const
    {
        return secondaryplayercarindex_->uint();
    }

} // namespace ris
