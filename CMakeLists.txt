cmake_minimum_required(VERSION 3.0.0)
project(risf12021 VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(CTest)
enable_testing()

add_library(risf12021 ./src/networkudp.cpp
                      ./src/networkfile.cpp
                      ./src/decoder.cpp
                      ./src/decoder1byte.cpp
                      ./src/decoder2bytes.cpp
                      ./src/decoder4bytes.cpp
                      ./src/decoder8bytes.cpp
                      ./src/packet.cpp
                      ./src/packetheader.cpp
                      ./src/packetevent.cpp
                      ./src/packetcarstatus.cpp
                      ./src/packetcartelemetrydata.cpp
                      ./src/value.cpp
                      )

add_executable(risf1 ./app/main.cpp)
target_link_libraries(risf1 risf12021)
install(TARGETS risf1
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

add_executable(testdecoders ./tests/test_decoders.cpp)
target_link_libraries(testdecoders risf12021)
add_test(NAME testdecoders COMMAND testdecoders)

add_executable(testpackets ./tests/test_packets.cpp)
target_link_libraries(testpackets risf12021)
add_test(NAME testpackets COMMAND testpackets)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
