
cmake_minimum_required(VERSION 3.6)
project(Transportation)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system-mt -lboost_serialization")

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

#[[set(BOOST_ROOT CACHE PATH "/usr/include/boost/")
find_package(Boost 1.58.0 COMPONENTS serialization system)
add_library(core ${core_SRCS})
target_link_libraries(core ${Boost_LIBRARIES})
include_directories(${Boost_INCLUDE_DIR})]]

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIR})

# see https://cmake.org/cmake/help/latest/module/FindBoost.html
find_package(Boost REQUIRED COMPONENTS)

include_directories(${Boost_INCLUDE_DIR})
# Note: a target should be already defined using 'add_executable' or 'add_library'
#target_link_libraries($TARGET$ ${Boost_LIBRARIES})


#[[find_package(Boost 1.58.0 REQUIRED COMPONENTS system filesystem)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${Boost_LIBRARY_DIRS})
target_link_libraries(${Boost_LIBRARIES})]]

set(SOURCE_FILES Cab.cpp Cab.h CarManufacturer.h Color.h Driver.cpp Driver.h MeritalStatus.h Trip.cpp Trip.h Point.cpp Point.h Map.cpp Map.h Location.cpp Location.h Passenger.cpp Passenger.h Road.cpp Road.h Tests/MapTester.cpp TaxiCenter.cpp TaxiCenter.h Search.h Tests/PointTester.cpp Tests/RoadTester.cpp Searchable.h Tests/TripTester.cpp Tests/PassengerTester.cpp Tests/SearchTester.cpp Tests/DriverTester.cpp Tests/TaxiCenterTester.cpp Tests/MainFlowTester.cpp Socket.cpp Socket.h ProcessRole.h Udp.cpp Udp.h Tcp.cpp Tcp.h Clock.h Clock.cpp ClientFlow.cpp ClientFlow.h ServerFlow.cpp ServerFlow.h)
add_executable(server server.cpp ${SOURCE_FILES} threadBFS.cpp threadBFS.h)
add_executable(client client.cpp ${SOURCE_FILES} )
target_link_libraries(server gtest gtest_main)
target_link_libraries(client gtest gtest_main)