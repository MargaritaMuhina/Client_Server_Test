#include "Socket.h"
#include "Client.h"
#include "Protocol.h"
#include <iostream>
#include <string>

int main() {
    Address address(DEFAULT_PORT, DEFAULT_HOST);
    Client client(address);

    // Define default frequency and power
    float frequency = 50.0f;  
    float power = 100.0f;     
    int command = -1;

    while (true) {
        // Display available commands to the user
        std::cout << "Choose a command:" << std::endl;
        std::cout << "1: I'm alive" << std::endl;
        std::cout << "2: Tell me your status" << std::endl;
        std::cout << "3: Set frequency (value)" << std::endl;
        std::cout << "4: Set power (value)" << std::endl;
        std::cout << "5: Tell me frequency" << std::endl;
        std::cout << "6: Tell me power" << std::endl;
        std::cout << "7: Raise emergency (number)" << std::endl;
        std::cout << "8: Clear emergency (number)" << std::endl;
        std::cout << "9: Tell me the list of raised emergencies" << std::endl;
        std::cout << "0: Exit" << std::endl;
        std::cout << "Enter command: ";
        std::cin >> command;

        if (command == 0) {
            std::cout << "Exit..." << std::endl;
            break;  
        }

        Protocol::Message request;
        switch (command) {
            case 1: 
                request.command = Protocol::ALIVE;
                break;
            case 2: 
                request.command = Protocol::STATUS;
                break;
            case 3: { 
                std::cout << "Enter frequency: ";
                std::cin >> frequency;

                request.command = Protocol::SET_FREQUENCY;
                request.data.resize(sizeof(float));  
                std::memcpy(request.data.data(), &frequency, sizeof(float));  // Copy the frequency value into the request data
                break;
            }
            case 4: { 
                std::cout << "Enter power: ";
                std::cin >> power;

                request.command = Protocol::SET_POWER;
                request.data.resize(sizeof(float));
                std::memcpy(request.data.data(), &power, sizeof(float)); // Copy the power value into the request data
                break;
            }
            case 5: 
                request.command = Protocol::GET_FREQUENCY;
                break;
            case 6: 
                request.command = Protocol::GET_POWER;
                break;
            case 7: { 
                int emergency;
                std::cout << "Enter emergency number: ";
                std::cin >> emergency;
                request.command = Protocol::RAISE_EMERGENCY;
                request.data.resize(sizeof(int));
                std::memcpy(request.data.data(), &emergency, sizeof(int)); // Copy the emergency number into the request data
                break;
            }
            case 8: { 
                int emergency;
                std::cout << "Enter emergency number to clear: ";
                std::cin >> emergency;
                request.command = Protocol::CLEAR_EMERGENCY;
                request.data.resize(sizeof(int));
                std::memcpy(request.data.data(), &emergency, sizeof(int)); // Copy the emergency number to clear into the request data
                break;
            }
            case 9: 
                request.command = Protocol::GET_EMERGENCIES;
                break;
            default:
                std::cerr << "Invalid command!" << std::endl;
                continue;  
        }

        try {
            client.SendRequest(request.command, request.data);  
            std::string response = client.ReceiveResponse();  

            if (command == 5) {  
                float received_frequency;
                std::memcpy(&received_frequency, response.data(), sizeof(float));
                std::cout << "Server response (Frequency): " << received_frequency << std::endl;
            }
            else if (command == 6) {  
                float received_power;
                std::memcpy(&received_power, response.data(), sizeof(float));
                std::cout << "Server response (Power): " << received_power << std::endl;
            } else if (command == 9) {  
                if (!response.empty()) {
                    std::cout << "Server response (Emergencies): ";
                    for (size_t i = 0; i < response.size() / sizeof(int); ++i) {
                        int emergency;
                        std::memcpy(&emergency, &response[i * sizeof(int)], sizeof(int));
                        std::cout << emergency << " ";
                    }
                    std::cout << std::endl;
                } else {
                    std::cout << "No emergencies raised." << std::endl;
                }
            } else {
                std::cout << "Server response: " << response << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Error sending/receiving data: " << e.what() << std::endl;
        }
    }

    return 0;
}
