#include <iostream>

#include "tests.h"
#include "../inc/networkfile.h"

#include "../inc/decoderuint8.h"
#include "../inc/decoderint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderuint64.h"
#include "../inc/decoderfloat.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{
    cout << "test decoders" << endl;

    try
    {
        DecoderUInt8 d;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            d.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x92);

        test_assert(d.decode(bytes, pos) == 146);
        test_assert(pos == 1);
        pos = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        DecoderInt8 d;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            d.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x92);

        test_assert(d.decode(bytes, pos) == -110);
        test_assert(pos == 1);
        pos = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        DecoderUInt16 d;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            d.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x92);
        bytes.push_back(0xCB);

        test_assert(d.decode(bytes, pos) == 52114);
        test_assert(pos == 2);
        pos = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }



    try
    {
        DecoderInt16 d;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            d.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x92);
        bytes.push_back(0xCB);

        test_assert(d.decode(bytes, pos) == -13422);
        test_assert(pos == 2);
        pos = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }


    try
    {
        DecoderUInt32 d;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            d.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x92);
        bytes.push_back(0xCB);
        bytes.push_back(0x8F);
        bytes.push_back(0xF0);

        test_assert(d.decode(bytes, pos) == 4035955602);
        test_assert(pos == 4);
        pos = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        DecoderFloat d;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            d.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x92);
        bytes.push_back(0xCB);
        bytes.push_back(0x8F);
        bytes.push_back(0xF0);

        test_assert(d.decode(bytes, pos) == -3.5601966249072491e+29);
        test_assert(pos == 4);
        pos = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }



    try
    {
        DecoderUInt64 d;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            d.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x10);
        bytes.push_back(0x01);
        bytes.push_back(0x01);
        bytes.push_back(0x01);
        bytes.push_back(0x01);
        bytes.push_back(0x01);
        bytes.push_back(0x01);
        bytes.push_back(0xF0);

        double a = d.decode(bytes, pos);
        test_assert(d.decode(bytes, pos) == 4043309073);
        test_assert(pos == 8);
        pos = 0;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
