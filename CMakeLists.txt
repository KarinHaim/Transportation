
cmake_minimum_required(VERSION 3.6)
project(Transportation)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_serialization -std=c++0x")

set(CMAKE_CXX_STANDARD 11)
add_subdirectory(lib/googletest-master)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(lib/googletest-master/googletest/include)
include_directories(lib/googletest-master/googlemock/include)

#set(Boost_USE_STATIC_LIBS on)
#set(BOOST_ROOT CACHE PATH "/usr/include/boost")
set(BOOST_ROOT CACHE PATH "/usr/include/boost_1_41_0/boost")
#set(BOOST_LIBRARYDIR "/usr/local/lib")
#set(BOOST_LIBRARYDIR "/usr/lib/x86_64-linux-gnu")
#set(BOOST_LIBRARYDIR "/usr/lib64")
#set(BOOST_LIBRARYDIR "/usr/include/boost_1_58_0/libs")
#set(BOOST_INCLUDEDIR "/usr/include/boost_1_41_0")
#set(BOOST_INCLUDEDIR "/usr/include/boost /usr/local/boost")
#find_package(Boost 1.41.0 COMPONENTS serialization system)
#find_package(Boost 1.41.0)
find_package(Boost 1.41.0 REQUIRED COMPONENTS serialization)
#add_library(core ${core_SRCS})
include_directories(${Boost_INCLUDE_DIR})

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_system -lboost_serialization")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lboost_serialization")

#set(SOURCE_FILES Cab.cpp Cab.h CarManufacturer.h Color.h Driver.cpp Driver.h MeritalStatus.h Trip.cpp Trip.h Point.cpp Point.h Map.cpp Map.h Location.cpp Location.h Passenger.cpp Passenger.h Road.cpp Road.h Socket.cpp Socket.h ProcessRole.h Udp.cpp Udp.h Tcp.cpp Tcp.h Clock.h Clock.cpp Serialization.h)
set(SOURCE_FILES src/Cab.cpp headers/Cab.h headers/CarManufacturer.h headers/Color.h src/Driver.cpp headers/Driver.h headers/MeritalStatus.h src/Trip.cpp headers/Trip.h src/Point.cpp headers/Point.h src/Map.cpp headers/Map.h src/Location.cpp headers/Location.h src/Passenger.cpp headers/Passenger.h src/Road.cpp headers/Road.h src/Socket.cpp headers/Socket.h headers/ProcessRole.h src/Udp.cpp headers/Udp.h src/Tcp.cpp headers/Tcp.h headers/Clock.h src/Clock.cpp headers/Serialization.h headers/easylogging++.h Tests/MapTester.cpp Tests/PointTester.cpp Tests/RoadTester.cpp Tests/TripTester.cpp Tests/PassengerTester.cpp Tests/SearchTester.cpp Tests/DriverTester.cpp Tests/TaxiCenterTester.cpp Tests/MainFlowTester.cpp)
add_executable(server src/server.cpp src/TaxiCenter.cpp headers/TaxiCenter.h src/ServerFlow.cpp headers/ServerFlow.h src/ClientHandleThread.cpp headers/ClientHandleThread.h src/CalculateRoadThread.cpp headers/CalculateRoadThread.h src/ThreadPool.cpp headers/ThreadPool.h src/Task.cpp headers/Task.h src/Vertex.cpp headers/Vertex.h src/SearchMap.cpp headers/SearchMap.h ${SOURCE_FILES})
add_executable(client src/client.cpp src/ClientFlow.cpp headers/ClientFlow.h ${SOURCE_FILES})

target_link_libraries(server ${Boost_LIBRARIES})
target_link_libraries(client ${Boost_LIBRARIES})

target_link_libraries(server gtest gtest_main)
target_link_libraries(client gtest gtest_main)
