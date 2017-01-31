
//#include <gtest/gtest.h>
#include <stdlib.h>
#include "ClientFlow.h"
#include "Tcp.h"
#include "easylogging++.h"

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

		ClientFlow mainFlow = ClientFlow();
		Driver* driver = mainFlow.scanDriver();
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