#include "Socket.h"

class Server {
public:

    Server(const Address& address, int backlog = 5) : socket(AF_INET, SOCK_STREAM, 0) {
        socket.Bind(address);
        socket.Listen(backlog);
    }

    
    void Accept_client() {
        int new_fd = socket.Accept();  
        Socket new_socket(new_fd);     

        
        std::string message = "OK!";
        new_socket.Send(message);  

        std::string received = new_socket.Receive();  
        std::cout << "Message from client: " << received << std::endl;
    }
private:
    Socket socket;
};
