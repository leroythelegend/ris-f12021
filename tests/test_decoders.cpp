#include <iostream>

#include "tests.h"
#include "../inc/networkfile.h"

#include "../inc/decoderuint64.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderuint8.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{
    cout << "test decoders" << endl;

    try
    {
        cout << "test decoderuint64" << endl;

        DecoderUInt64 decoder;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            decoder.decode(bytes, pos);
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
        bytes.push_back(0x00);

        decoder.decode(bytes, pos);
        test_assert(decoder.uint() == 282578800148752);
        test_assert(pos == 8);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        cout << "test decoderuint16" << endl;

        DecoderUInt16 decoder;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            decoder.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x10);
        bytes.push_back(0x01);

        decoder.decode(bytes, pos);
        test_assert(decoder.uint() == 272);
        test_assert(pos == 2);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    try
    {
        cout << "test decoderuint8" << endl;

        DecoderUInt8 decoder;
        Bytes bytes;
        unsigned int pos = 0;

        try
        {
            decoder.decode(bytes, pos);
            test_assert(false);
        }
        catch (const std::exception &e)
        {
        }

        bytes.push_back(0x10);

        decoder.decode(bytes, pos);
        test_assert(decoder.uint() == 16);
        test_assert(pos == 1);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }

    return 0;
}
