#include <iostream>

#include "tests.h"
#include "../inc/networkfile.h"

#include "../inc/decoderuint16.h"

using namespace std;
using namespace ris;

int main(int argc, char const *argv[])
{
    cout << "test decoders" << endl;

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

    return 0;
}
