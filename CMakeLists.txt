cmake_minimum_required(VERSION 3.6)
project(Transportation)

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)


set(SOURCE_FILES main.cpp Cab.cpp Cab.h CarManufacturer.h Color.h Driver.cpp Driver.h MeritalStatus.h Trip.cpp Trip.h Point.cpp Point.h Map.cpp Map.h Location.cpp Location.h Passenger.cpp Passenger.h Road.cpp Road.h Tests/MapTester.cpp TaxiCenter.cpp TaxiCenter.h StandardCab.cpp StandardCab.h Search.h MainFlow.cpp MainFlow.h Tests/PointTester.cpp Tests/RoadTester.cpp LuxuryCab.cpp LuxuryCab.h Searchable.h Tests/TripTester.cpp Tests/PassengerTester.cpp Tests/SearchTester.cpp Tests/DriverTester.cpp Tests/TaxiCenterTester.cpp Tests/MainFlowTester.cpp Socket.cpp Socket.h ProcessRole.h Udp.cpp Udp.h Tcp.cpp Tcp.h)
add_executable(Transportation ${SOURCE_FILES})
target_link_libraries(Transportation gtest gtest_main)

set(BOOST_ROOT "/usr/local/boost_1_62_0")
find_package(Boost 1.62.0 REQUIRED COMPONENTS)
include_directories(${Boost_INCLUDE_DIR})
target_link_libraries(Transportation ${Boost_LIBRARIES})
