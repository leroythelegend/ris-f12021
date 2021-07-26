#pragma once

#include "network.h"

#include <string>

namespace ris
{
    class NetworkFile : public Network
    {
    public:
        using FileName = std::string;

        NetworkFile(const FileName &);
        ~NetworkFile() override = default;

        Bytes read() const override;
    private:
        FileName filename_;
    };
} // namespace ris
