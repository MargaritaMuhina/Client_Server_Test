#pragma once
#include "Socket.h"
#include "Protocol.h"
#include <iostream>
#include <algorithm>
#include <vector>

class Server {
public:
    Server(const Address& address, int backlog = 5) : socket(AF_INET, SOCK_STREAM, 0) {
        socket.Bind(address);  
        socket.Listen(backlog);  
    }

    void Accept_client() {
        int new_fd = socket.Accept();  
        Socket new_socket(new_fd);     

        std::string client_msg = new_socket.Receive();  
        std::vector<uint8_t> buffer(client_msg.begin(), client_msg.end());

        Protocol::Message request = Protocol::Deserialize(buffer);  

        Protocol::Message response;
        response.command = request.command;

        switch (request.command) {
            case Protocol::ALIVE:
                response.data = {'O', 'K'};
                break;
            case Protocol::STATUS:
                response.data = {'G', 'O', 'O', 'D'};
                break;
            case Protocol::SET_FREQUENCY: {
                if (request.data.size() == sizeof(float)) {
                    std::memcpy(&current_frequency, request.data.data(), sizeof(float));
                }
                response.data = {'O', 'K'};
                break;
            }
            case Protocol::SET_POWER: {
                if (request.data.size() == sizeof(float)) {
                    std::memcpy(&current_power, request.data.data(), sizeof(float));
                }
                response.data = {'O', 'K'};
                break;
            }
            case Protocol::GET_FREQUENCY: {
                response.data.resize(sizeof(float));  
                std::memcpy(response.data.data(), &current_frequency, sizeof(float));  
                break;
            }
            case Protocol::GET_POWER: {
                response.data.resize(sizeof(float));  
                std::memcpy(response.data.data(), &current_power, sizeof(float));  
                break;
            }
            case Protocol::RAISE_EMERGENCY: {
                if (request.data.size() == sizeof(int)) {
                    int emergency = *reinterpret_cast<int*>(request.data.data());
                    emergencies.push_back(emergency);
                }
                response.data = {'O', 'K'};
                break;
            }
            case Protocol::CLEAR_EMERGENCY: {
                if (request.data.size() == sizeof(int)) {
                    int emergency = *reinterpret_cast<int*>(request.data.data());
                    emergencies.erase(std::remove(emergencies.begin(), emergencies.end(), emergency), emergencies.end());
                }
                response.data = {'O', 'K'};
                break;
            }
            case Protocol::GET_EMERGENCIES: {
                response.data.resize(emergencies.size() * sizeof(int));
                std::memcpy(response.data.data(), emergencies.data(), emergencies.size() * sizeof(int));
                break;
            }
            default:
                response.data = {'E', 'R', 'R', 'O', 'R'};
                break;
        }

        auto serialized_response = Protocol::Serialize(response);  
        new_socket.Send(std::string(serialized_response.begin(), serialized_response.end()));  

        std::cout << "Processed command: " << static_cast<int>(request.command) << std::endl;

        close(new_fd);
    }

private:
    Socket socket;
    float current_frequency = 50.0f;  
    float current_power = 100.0f;     
    std::vector<int> emergencies;     
};
