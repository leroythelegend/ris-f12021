#include "../inc/networkfile.h"

#include <fstream>
#include <iterator>

using namespace std;

namespace ris
{

    NetworkFile::NetworkFile(const FileName &filename)
        : filename_{filename} {}

    Bytes NetworkFile::read() const
    {
        // open the file:
        std::ifstream file(filename_, std::ios::binary);

        // Stop eating new lines in binary mode!!!
        file.unsetf(std::ios::skipws);

        // get its size:
        std::streampos fileSize;

        file.seekg(0, std::ios::end);
        fileSize = file.tellg();
        file.seekg(0, std::ios::beg);

        // reserve capacity
        Bytes vec;
        vec.reserve(fileSize);

        // read the data:
        vec.insert(vec.begin(),
                   std::istream_iterator<unsigned char>(file),
                   std::istream_iterator<unsigned char>());

        return vec;
    }

} // namespace ris
