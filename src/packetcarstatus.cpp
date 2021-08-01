#include "../inc/packetcarstatus.h"
#include "../inc/packetheader.h"

namespace ris
{

    PacketCarStatus::PacketCarStatus(const Bytes &bytes, Pos &pos)
    {
        Packet::add(PacketHeader::PACKETHEADER, std::vector<Packet::Ptr>{std::make_shared<PacketHeader>(bytes, pos)});
    }

} // namespace ris
