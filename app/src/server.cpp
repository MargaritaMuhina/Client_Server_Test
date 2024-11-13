#include "Socket.h"
#include "Server.h"
#include "Protocol.h"
#include <iostream>
#include <string>

int main() {
    // Define the address of the server (port and host)
    Address address(DEFAULT_PORT, DEFAULT_HOST);
    // Create a Server instance and bind it to the address
    Server server(address);

    std::cout << "Server started, waiting for connections..." << std::endl;
    // Enter an infinite loop to continuously accept client connections
    while (true) {
        try {
            // Accept a client connection and process its request
            server.Accept_client();  
        } catch (const std::exception& e) {
            std::cerr << "Error during communication: " << e.what() << std::endl;
            break;
        }
    }
    std::cout << "Server exiting..." << std::endl;
    return 0;
}
