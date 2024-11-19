#include "Server.h"
#include <iostream>

int main() {
    // Define the address of the server (port and host)
    Address address(DEFAULT_PORT, DEFAULT_HOST);
    // Create a Server instance and bind it to the address
    Server server(address);
    server.Run();
    return 0;
}
