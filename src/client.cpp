
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
        std::vector<std::string> DriverArguments;
        DriverArguments[0] = argv[3];
        DriverArguments[1] = argv[4];
        DriverArguments[2] = argv[5];
        DriverArguments[3] = argv[6];
        DriverArguments[4] = argv[7];

		ClientFlow mainFlow = ClientFlow();
		Driver* driver = mainFlow.scanDriver(DriverArguments);
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