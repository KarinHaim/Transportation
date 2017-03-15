
//#include <gtest/gtest.h>
#include <stdlib.h>
#include <sstream>
#include "../headers/Udp.h"
#include "../headers/ServerFlow.h"
#include "../headers/Tcp.h"
#include "../headers/easylogging++.h"

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
    Socket* socket = new Tcp(ProcessRole::SERVER, (u_short)port);
    mainFlow.setSocket(socket);

    std::string operationNum;
	try {
		while(true) {
			do {
				//getline(cin, operationNum);
                char buffer[40000] = { 0 };
                socket->receiveData(buffer, sizeof(buffer));
                std::string operationNum(buffer);
				if(!isNumber(operationNum)){
                    socket->sendData("error");
					continue;
				}
				break;
			} while (true);
			int newOperationNum = stoi(operationNum);
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
				/*case 4:
					LOG(DEBUG) << "printDriversLocation\n";
					mainFlow.printDriversLocation();
					break;*/
				case 7:
					LOG(DEBUG) << "exitSignal\n";
					mainFlow.exitSignal();
					return 0;
					break;
				case 9:
					mainFlow.updateTime();
                    break;
				default:
                    socket->sendData("error");
					break;
			}
		}
	} catch (const char * s) {
        LOG(DEBUG) << "the exception is " << s;
	}
}

