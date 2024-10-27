#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <errno.h>
#include "erproc.h"

int main() {

    // Create a socket for the server
    int server = Socket(AF_INET, SOCK_STREAM, 0);

    // Define the server's address information
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543); // Port number
    Bind(server, (struct sockaddr *) &adr, sizeof adr); // Bind the socket to the address

    // Start listening for connections
    Listen(server, 5);
    // Accept a connection from a client
    socklen_t adrlen = sizeof adr;
    int client = Accept(server, (struct sockaddr *) &adr, &adrlen);

    // Read the message from the client
    ssize_t nread;
    char buf[256];
    try {
        nread = read(client, buf, 256);
        if (nread == -1) {
            throw std::runtime_error(std::string("read failed: ") + strerror(errno));
        } else if (nread == 0) {
            std::cout << "END OF FILE occurred"<< std::endl;
        }
        // Print the received message
        std::cout.write(buf, nread);
        // Send "Ok" to the client
        std::string response = "Ok";
        if (write(client, response.c_str(), response.length()) == -1) {
            throw std::runtime_error(std::string("write failed: ") + strerror(errno));
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
    sleep(10);
    close(client);
    close(server);
    return 0;
}