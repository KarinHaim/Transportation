
//#include <gtest/gtest.h>
#include <stdlib.h>
#include "../headers/ClientFlow.h"
#include "../headers/Tcp.h"
#include "../headers/easylogging++.h"

_INITIALIZE_EASYLOGGINGPP

/**
 * this is the main function which operates the program of the client side.
 * @param argc  - number of arguments to main.
 * @param argv - the argumenrs.
 * @return
 */
int main(int argc, char* argv[]) {

	try {
		const char * ip = argv[1];
		int port = atoi(argv[2]);
        std::vector<std::string> driverArguments;
        driverArguments[0] = argv[3];
        driverArguments[1] = argv[4];
        driverArguments[2] = argv[5];
        driverArguments[3] = argv[6];
        driverArguments[4] = argv[7];

		ClientFlow mainFlow = ClientFlow();
		Driver* driver = mainFlow.scanDriver(driverArguments);
		mainFlow.setSocket(new Tcp(ProcessRole::CLIENT, (u_short)port, ip));
		mainFlow.addDriver(driver);
		mainFlow.flow();
	} catch (boost::archive::archive_exception & boost_exception) {
        LOG(DEBUG) << boost_exception.what();
	} catch (...) {
        LOG(DEBUG) << "Unhandled exception\n";
	}

    return 0;
}