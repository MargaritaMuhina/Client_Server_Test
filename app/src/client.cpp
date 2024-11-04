#include "Socket.h"

#include <iostream>
#include <string>


int main() {
    Address address(DEFAULT_PORT, DEFAULT_HOST);

    Client client(address);

    std::cout << "Enter a message: ";
    std::string message;
    std::cin >> message;

    if (!message.empty()) {
        try {
            client.Send(message);
            std::cout << "Server response: " << client.Receive() << std::endl;
        }catch (const std::exception& e) {
            std::cerr << "Error sending message: " << e.what() << std::endl;
        }
        
    } else {
        std::cerr << "You did not enter a message." << std::endl;
    }
    return 0;
}
