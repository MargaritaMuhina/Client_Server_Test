#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <stdexcept>
#include <errno.h>
#include "erproc.h"

int main() {

    // Create a socket for the client
    int client = Socket(AF_INET, SOCK_STREAM, 0);
    // Define the server's address information
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543); // Port number to connect to
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr); // Server's IP address

    // Connect to the server
    Connect(client, (struct sockaddr *) &adr, sizeof adr);

    // Get a message from the user
    std::string message;
    std::cout << "Enter a message: ";
    std::getline(std::cin, message);

    // Send the message to the server if it is not empty
    if (!message.empty()) {
        const char* message_c_str = message.c_str();
        write(client, message_c_str, strlen(message_c_str));

        // Read the response from the server
        char buf[256];
        ssize_t nread;
        try {
            nread = read(client, buf, 256);
            if (nread == -1) {
                throw std::runtime_error(std::string("read failed: ") + strerror(errno));
            }
            else if (nread == 0) {
        	std::cout << "END OF FILE occurred "<< std::endl;
		}
            // Print the server's response
            std::cout.write(buf, nread);
        } catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << std::endl;
        }

    } else {
        std::cerr << "You did not enter a message." << std::endl;
    }



    sleep(10); 
    close(client); // Close the socket
    return 0;
}



