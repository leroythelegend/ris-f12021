#pragma once

#include <cstddef>
#include <vector>

namespace ris
{
    using Bytes = std::vector<unsigned char>;
    using Pos = unsigned int;
    using Amount = int;

    const int NUMBEROFPARTICIPANTS = 22;
    const int MAXNUMMARSHALZONES = 21;
    const int MAXNUMWEATHERFORECASTSAMPLES = 56;

    enum class PacketID
    {
        Motion,
        Session,
        Lap_Data,
        Event,
        Participants,
        Car_Setups,
        Car_Telemetry,
        Car_Status,
        Final_Classification,
        Lobby_Info,
        Car_Damage,
        Session_History
    };
} // namespace ris
