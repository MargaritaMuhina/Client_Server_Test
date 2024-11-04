#include "Socket.h"

#include <iostream>
#include <string>


int main() {
    Address address(DEFAULT_PORT, DEFAULT_HOST);

    Server server(address);

    std::cout << "Server started, waiting for connections..." << std::endl;

    try {
        Client client = server.Accept_client();

        std::string message = client.Receive();
        if (message.empty()) {
            std::cout << "Client disconnected." << std::endl;
        }
        
        std::cout << "Client message: " << message << std::endl;

        client.Send("Ok");
    }catch (const std::exception& e) {
        std::cerr << "Error sending message: " << e.what() << std::endl;
    }

    return 0;
}
