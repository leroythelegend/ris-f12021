#include "../inc/capturecsv.h"
#include "../inc/processcartelemetry.h"
#include "../inc/recordcsv.h"

#include <iostream>
#include <stdexcept>
#include <memory>
#include <thread>

unsigned int getPortFromArgs(int argc, char const *argv[]);

int main(int argc, char const *argv[])
{
    try
    {
        unsigned int port = getPortFromArgs(argc, argv);
        std::thread start([](unsigned int port_)
                          {
                              ris::CaptureCSV capture(port_, std::make_shared<ris::ProcessCarTelemetry>(std::make_shared<ris::RecordCSV>()));
                              capture.start();
                          },
                          port);
        start.detach();

        std::thread quit([]()
                         {
                             std::cout << "Press \'q\' then \'Enter\' to QUIT." << std::endl;
                             while (true)
                             {
                                 char key;
                                 std::cin >> key;
                                 if (key == 'q')
                                 {
                                     return 0;
                                 }
                             }
                         });

        quit.join();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }

    return 0;
}

unsigned int getPortFromArgs(int argc, char const *argv[])
{
    if (argc == 2)
    {
        return std::stoul(argv[1]);
    }
    return 20777;
}
