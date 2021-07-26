#pragma once

#include "network.h"

namespace ris
{
    class NetworkUDP : public Network
    {
    public:
        using Port = unsigned int;

        NetworkUDP(const Port &);
        ~NetworkUDP() override;

        Bytes read() const override;
    private:
        class NetworkUDPImpl;
        std::unique_ptr<NetworkUDPImpl> impl_;
    };
} // namespace ris
