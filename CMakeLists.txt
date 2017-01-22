cmake_minimum_required(VERSION 3.6)
project(Transportation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system -lboost_serialization")

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

set(SOURCE_FILES Cab.cpp Cab.h CarManufacturer.h Color.h Driver.cpp Driver.h MeritalStatus.h Trip.cpp Trip.h Point.cpp Point.h Map.cpp Map.h Location.cpp Location.h Passenger.cpp Passenger.h Road.cpp Road.h Tests/MapTester.cpp Search.h Tests/PointTester.cpp Tests/RoadTester.cpp Tests/TripTester.cpp Tests/PassengerTester.cpp Tests/SearchTester.cpp Tests/DriverTester.cpp Tests/TaxiCenterTester.cpp Tests/MainFlowTester.cpp Socket.cpp Socket.h ProcessRole.h Udp.cpp Udp.h Tcp.cpp Tcp.h Clock.h Clock.cpp Serialization.h)
add_executable(server server.cpp TaxiCenter.cpp TaxiCenter.h ServerFlow.cpp ServerFlow.h ClientHandleThread.cpp ClientHandleThread.h CalculateRoadThread.cpp CalculateRoadThread.h ${SOURCE_FILES})
add_executable(client client.cpp ClientFlow.cpp ClientFlow.h ${SOURCE_FILES})
target_link_libraries(server gtest gtest_main)
target_link_libraries(client gtest gtest_main)

set(BOOST_ROOT "/usr/include/boost_1_58_0")
find_package(Boost 1.58.0 COMPONENTS serialization system)
#add_library(core ${core_SRCS})
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})