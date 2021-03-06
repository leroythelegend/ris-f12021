cmake_minimum_required(VERSION 3.0.0)
project(risf12021 VERSION 1.0.4)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

include(CTest)
enable_testing()

add_library(risf12021 ./src/networkudp.cpp
                      ./src/networkfile.cpp
                      ./src/decoderuint8.cpp
                      ./src/decoderuint16.cpp
                      ./src/decoderuint32.cpp
                      ./src/decoderint8.cpp
                      ./src/decoderint16.cpp
                      ./src/decoderfloat.cpp
                      ./src/decoderdouble.cpp
                      ./src/decoderuint64.cpp
                      ./src/packet.cpp
                      ./src/packetheader.cpp
                      ./src/packetevent.cpp
                      ./src/packetcarstatus.cpp
                      ./src/packetcarsetupdata.cpp
                      ./src/packetcartelemetrydata.cpp
                      ./src/packetmotiondata.cpp
                      ./src/packetsessiondata.cpp
                      ./src/packetlapdata.cpp
                      ./src/packetparticipantsdata.cpp
                      ./src/packetfinalclassificationdata.cpp
                      ./src/packetlobbyinfodata.cpp
                      ./src/packetsessionhistorydata.cpp
                      ./src/packetcardamagedata.cpp
                      ./src/value.cpp
                      ./src/csv.cpp
                      ./src/capturefrontendstate.cpp
                      ./src/capturepitstate.cpp
                      ./src/capturelapstate.cpp
                      ./src/capturerecordstate.cpp
                      ./src/capturecsv.cpp
                      ./src/processcartelemetry.cpp
                      ./src/recordcsv.cpp
                      ./src/state.cpp
                      )

add_executable(risf1 ./app/main.cpp)
target_link_libraries(risf1 risf12021
                      Threads::Threads
                      )
install(TARGETS risf1
    DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)

add_executable(testdecoders ./tests/test_decoders.cpp)
target_link_libraries(testdecoders risf12021)
add_test(NAME testdecoders COMMAND testdecoders)

add_executable(testpackets ./tests/test_packets.cpp)
target_link_libraries(testpackets risf12021)
add_test(NAME testpackets COMMAND testpackets)

add_executable(testcsv ./tests/test_csv.cpp)
target_link_libraries(testcsv risf12021)
add_test(NAME testcsv COMMAND testcsv)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
