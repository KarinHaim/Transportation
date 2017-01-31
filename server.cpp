
//#include <gtest/gtest.h>
#include <stdlib.h>
#include <sstream>
#include "Udp.h"
//#include "Serialization.h"
#include "ServerFlow.h"
#include "Tcp.h"
#include "easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

/**
 * this is the main function which operates the program of the server side.
 * @param argc  - number of arguments to main.
 * @param argv - the argumenrs.
 * @return
 */
int main(int argc, char* argv[]) {
    int port = atoi(argv[1]);


    ServerFlow mainFlow = ServerFlow();
    mainFlow.setWorldRepresentation();
	mainFlow.setSocket(new Tcp(ProcessRole::SERVER, (u_short)port));
	
    int operationNum;
	try {
		while(true) {
			do {
				std::cin.clear();
				std::cin >> operationNum;
			} while (std::cin.fail() && EINTR == errno);
			if (std::cin.fail())
				throw "not a number";
			if (operationNum < 1 || operationNum > 9 || operationNum == 5 || operationNum == 6
					|| operationNum == 8)
				throw "invalid operation number";
			switch (operationNum) {
				case 1:
					LOG(DEBUG) << "addDrivers\n";
					mainFlow.addDrivers();
					break;
				case 2:
					LOG(DEBUG) << "addTrip\n";
					mainFlow.addTrip();
					break;
				case 3:
					LOG(DEBUG) << "addTaxi\n";
					mainFlow.addTaxi();
					break;
				case 4:
					LOG(DEBUG) << "printDriversLocation\n";
					mainFlow.printDriversLocation();
					break;
				case 7:
					LOG(DEBUG) << "exitSignal\n";
					mainFlow.exitSignal();
					return 0;
					break;
				case 9:
					mainFlow.updateTime();
			}
		}
	} catch (const char * s) {
        LOG(DEBUG) << "the exception is " << s;
	}
}