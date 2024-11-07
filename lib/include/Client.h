#pragma once
#include "Socket.h"
#include "Protocol.h"
#include <vector>
#include <string>

class Client {
public:
    Client(const Address& address) : socket(AF_INET, SOCK_STREAM, 0) {
        socket.Connect(address);
    }

    
    void SendRequest(Protocol::Command cmd, const std::vector<uint8_t>& data = {}) {
        // Create a message containing the command and the data to be sent
        Protocol::Message msg{cmd, data};               
        auto serialized = Protocol::Serialize(msg);    

        // Send the serialized message as a string over the socket 
        socket.Send(std::string(serialized.begin(), serialized.end()));  
    }

    
    std::string ReceiveResponse() {
        
        std::string response = socket.Receive();
        // Convert the received string into a vector of bytes for deserialization
        std::vector<uint8_t> buffer(response.begin(), response.end());
        
        try {
            Protocol::Message msg = Protocol::Deserialize(buffer);
            // Convert the message data into a string 
            std::string responseStr(msg.data.begin(), msg.data.end());
            return responseStr;
        } catch (const std::exception& e) {
            std::cerr << "Error during deserialization: " << e.what() << std::endl;
            return "";
        }
    }

private:
    Socket socket;   
};
