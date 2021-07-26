#include "../inc/networkudp.h"

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    ris::NetworkUDP network(20777);

    ris::Bytes bytes = network.read();

    // just want to create some test vectors so write to file
    // then I will subclass a NetworkFile from Network to test
    // decoders

    // ofstream outfile("/tmp/f12021.out", ios::out|ios::binary);
    // cout << "captured size " << bytes.size() << endl;
    // outfile.write(reinterpret_cast<const char *>(bytes.data()), bytes.size());

    return 0;
}
