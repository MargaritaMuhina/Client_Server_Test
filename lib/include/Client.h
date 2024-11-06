#include "Socket.h"

class Client {
public:
    Client(const Address& address) : socket(AF_INET, SOCK_STREAM, 0) {
        socket.Connect(address);
    }

    // Method to send a message to the server
    void Send(const std::string& message) {
        socket.Send(message);
    }

    // Method to receive a response from the server
    std::string Receive() {
        return socket.Receive();
    }

private:
    Socket socket;
};
