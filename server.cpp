
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
	
    std::string operationNum;
	try {
		while(true) {
			do {
				//std::cin.clear();
				//std::cin >> operationNum;
				getline(cin, operationNum);
				if(stoi(operationNum) < 0) {
					cout << "-1" << endl;
					continue;
				}
				break;
			} while (true);
			int newOperationNum = stoi(operationNum);
			if (std::cin.fail())
				throw "not a number";
			if (newOperationNum < 1 || newOperationNum > 9 || newOperationNum == 5 || newOperationNum == 6
					|| newOperationNum == 8)
				throw "invalid operation number";
			switch (newOperationNum) {
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
/*
static bool isNumber(const std::string &s) {
	std::string::const_iterator it = s.begin();
	while (it != s.end() && std::isdigit(*it)) ++it;
	return !s.empty() && it == s.end();
}*/
