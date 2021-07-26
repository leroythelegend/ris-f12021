#include "../inc/networkudp.h"

#ifdef _WIN32

#define close closesocket

#pragma comment(lib, "Ws2_32.lib")
#include <Ws2tcpip.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <cstring>
#include <unistd.h>

#endif

#include <string>
#include <iostream>

using namespace std;

namespace ris
{
    class NetworkUDP::NetworkUDPImpl
    {
    public:
        unsigned int AMOUNT = 2048;

        NetworkUDPImpl(const Port &port)
        {
#ifdef _WIN32

#define close closesocket

            WORD wVersionRequested;
            WSADATA wsaData;

            /* Use the MAKEWORD(lowbyte, highbyte) macro declared in Windef.h */
            wVersionRequested = MAKEWORD(2, 2);

            WSAStartup(wVersionRequested, &wsaData);
            struct sockaddr_in server, si_other;
            int slen;

            slen = sizeof(si_other);

            //Create a socket
            if ((socketfd_ = socket(AF_INET, SOCK_DGRAM, 0)) == INVALID_SOCKET)
            {
                throw runtime_error("socket " + WSAGetLastError());
            }

            BOOL bOptVal = TRUE;
            int bOptLen = sizeof(BOOL);
            if (setsockopt(socketfd_, SOL_SOCKET, SO_REUSEADDR, (char *)&bOptVal, sizeof(bOptLen)) == SOCKET_ERROR)
            {
                cout << "setsockopt" << endl;
                ::close(socketfd_);
                throw runtime_error("setsockopt " + WSAGetLastError());
            }

            //Prepare the sockaddr_in structure
            server.sin_family = AF_INET;
            server.sin_addr.s_addr = INADDR_ANY;
            server.sin_port = htons(port);

            //Bind
            if (bind(socketfd_, (struct sockaddr *)&server, sizeof(server)) == SOCKET_ERROR)
            {
                throw runtime_error("bind " + WSAGetLastError());
            }
#else

            struct addrinfo hints, *servinfo, *p;
            int rv = 0;

            string sport = to_string(port);

            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_UNSPEC; // set to AF_INET to force IPv4
            hints.ai_socktype = SOCK_DGRAM;
            hints.ai_flags = AI_PASSIVE; // use my IP

            if ((rv = getaddrinfo(NULL, sport.c_str(), &hints, &servinfo)) != 0)
            {
                string msg("getaddrinfo error ");
                msg.append(gai_strerror(rv));
                throw runtime_error(msg);
            }

            // loop through all the results and bind to the first we can

            for (p = servinfo; p != NULL; p = p->ai_next)
            {
                if ((socketfd_ = socket(p->ai_family, p->ai_socktype,
                                        p->ai_protocol)) == -1)
                {
                    continue;
                }

                int one = 1;
                if (setsockopt(socketfd_, SOL_SOCKET, SO_REUSEPORT, &one, sizeof(one)))
                {
                    ::close(socketfd_);
                    continue;
                }

                if (::bind(socketfd_, p->ai_addr, p->ai_addrlen))
                {
                    ::close(socketfd_);
                    continue;
                }

                break;
            }

            if (p == NULL)
            {
                string msg("socket or bind ");
                msg.append(to_string(errno));
                throw runtime_error(msg);
            }

            freeaddrinfo(servinfo);
#endif // _WIN32
        }

        ~NetworkUDPImpl()
        {
            close(socketfd_);
        }

        Bytes read() const
        {
            int numbytes = 0;
            struct sockaddr_storage their_addr;
            socklen_t addr_len = sizeof their_addr;

            Bytes buffer(AMOUNT);

#ifdef _WIN32
            if ((numbytes = recvfrom(socketfd_, reinterpret_cast<char *>(buffer.data()), AMOUNT, 0,
                                     (struct sockaddr *)&their_addr, &addr_len)) == -1)
            {
                throw runtime_error("recvfrom");
            }
#else
            if ((numbytes = recvfrom(socketfd_, buffer.data(), AMOUNT, 0,
                                     (struct sockaddr *)&their_addr, &addr_len)) == -1)
            {
                throw runtime_error("recvfrom");
            }
#endif

            buffer.resize(numbytes);

            return buffer;
        }

    private:
#ifdef _WIN32
        SOCKET socketfd_;
#else
        int socketfd_;
#endif
    };

    NetworkUDP::NetworkUDP(const Port &port)
        : impl_{make_unique<NetworkUDPImpl>(port)} {}

    NetworkUDP::~NetworkUDP() {}

    Bytes NetworkUDP::read() const
    {
        return impl_->read();
    }

} // namespace ris
