#include "Socket.h"
#include "Client.h"
#include "Protocol.h"
#include "ClientCommandHandler.h"
#include <iostream>
#include <string>

int main() {
    Address address(DEFAULT_PORT, DEFAULT_HOST);    // Default address of the server
    ClientCommandHandler commandHandler;            // Command handler to process user input
    
    int command = -1;

    while (true) {
        Client client(address);                 // Client object responsible for network communication
        commandHandler.ShowCommands();          // Show all available commands
        std::cin >> command;

        if (command == 0) {
            std::cout << "Exit..." << std::endl;
            // Send EXIT command to the server
            Protocol::Message exit_msg;
            exit_msg.command = Protocol::EXIT;  
            client.SendRequest(exit_msg.command, exit_msg.data);
            break;  
        }
        // Prepare the message based on user input
        Protocol::Message request = commandHandler.HandleCommand(command);

        try {
            client.SendRequest(request.command, request.data);      // Send the prepared request to the server
            std::string response = client.ReceiveResponse();        // Receive the response from the server

            commandHandler.ProcessServerResponse(command, response);

        } catch (const std::exception& e) {
            std::cerr << "Error sending/receiving data: " << e.what() << std::endl;
        }
    }

    return 0;
}
