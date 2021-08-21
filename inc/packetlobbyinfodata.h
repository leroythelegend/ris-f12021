#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketLobbyInfoData : public Packet
    {
    public:
        class LobbyInfoData : public SubPacket
        {
        public:
            inline static const Element AICONTROLLED{"AICONTROLLED"};
            inline static const Element TEAMID{"TEAMID"};
            inline static const Element NATIONALITY{"NATIONALITY"};
            inline static const Element NAME{"NAME"};
            inline static const Element CARNUMBER{"CARNUMBER"};
            inline static const Element READYSTATUS{"READYSTATUS"};

            inline static const Element LOBBYINFODATA{"LOBBYINFODATA"};

            LobbyInfoData(const Bytes &, Pos &);
            ~LobbyInfoData() override = default;
        };

        class NumPlayers : public SubPacket
        {
        public:
            inline static const Element NUMLOBBYPLAYERS{"NUMLOBBYPLAYERS"};

            inline static const Element NUMPLAYERS{"NUMPLAYERS"};

            NumPlayers(const Bytes &, Pos &);
            ~NumPlayers() override = default;
        };

        PacketLobbyInfoData(const Bytes &);
        ~PacketLobbyInfoData() override = default;
    };

} // namespace ris
