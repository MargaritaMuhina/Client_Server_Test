#include "Socket.h"
#include "Server.h"
#include <iostream>
#include <string>

int main() {
    Address address(DEFAULT_PORT, DEFAULT_HOST);

    Server server(address);

    std::cout << "Server started, waiting for connections..." << std::endl;

    try {
        server.Accept_client(); 

    } catch (const std::exception& e) {
        std::cerr << "Error during communication: " << e.what() << std::endl;
    }

    return 0;
}
