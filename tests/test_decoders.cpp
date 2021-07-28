#include <iostream>

#include "tests.h"
#include "../inc/networkfile.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder2bytes.h"
#include "../inc/decoder4bytes.h"
#include "../inc/decoder8bytes.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{
    cout << "test decoders" << endl;

    try
    {
        Decoder1Byte d;
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

        d.decode(bytes, pos);
        test_assert(d.element().Float == 2.04589576e-43F);
        test_assert(pos == 1);

        test_assert(d.element().UInt == 146);
        test_assert(pos == 1);

        test_assert(d.element().SInt == -110);
        test_assert(pos == 1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        Decoder2Bytes d;
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

        d.decode(bytes, pos);
        test_assert(d.element().Float == 7.30273e-41F);
        test_assert(pos == 2);

        test_assert(d.element().UInt == 52114);
        test_assert(pos == 2);

        test_assert(d.element().SInt == -13422);
        test_assert(pos == 2);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        Decoder4Bytes d;
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

        d.decode(bytes, pos);
        test_assert(d.element().Float == -3.56019662e+29F);
        test_assert(pos == 4);

        test_assert(d.element().UInt == 18446744073450539922U);
        test_assert(pos == 4);

        test_assert(d.element().SInt == -259011694);
        test_assert(pos == 4);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        Decoder8Bytes d;
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

        d.decode(bytes, pos);
        test_assert(d.element().Float == 0);
        test_assert(pos == 8);

        test_assert(d.element().UInt == 17294105147902853392U);
        test_assert(pos == 8);

        test_assert(d.element().SInt == -1152638925806698224);
        test_assert(pos == 8);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
