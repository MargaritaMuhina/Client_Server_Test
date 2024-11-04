#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <string>
#include <iostream>
#include <unistd.h>
#include <cstring>


#define DEFAULT_PORT 34543
#define DEFAULT_HOST "127.0.0.1"
#define DEFAULT_BUF 256

// Structure to store the address
struct Address {
    uint16_t port;
    std::string host;

    Address(uint16_t port, const std::string& host) : port(port), host(host) {}
};


class Socket {
public:
    Socket(int domain, int type, int protocol) : fd(socket(domain, type, protocol)) {
        if (fd == -1) {
            throw std::runtime_error("Socket creation failed: " + std::string(strerror(errno)));
        }
    }

    ~Socket() {
        if (fd != -1) {
            close(fd);
        }
    }

    // Method to establish a connection with another socket
    void Connect(const Address& address);

    // Method to send data to the socket
    void Send(const std::string& message);

    // Method to receive data from the socket
    std::string Receive();

    // Method to bind the socket to an address
    void Bind(const Address& address);

    // Method to listen for incoming connections
    void Listen(int backlog);

    // Method to accept a new connection
    int Accept();

    // Method to get the socket descriptor
    int get_fd() {
        return fd;
    }

private:
    int fd;
};


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


class Server {
public:

    Server(const Address& address, int backlog = 5) : socket(AF_INET, SOCK_STREAM, 0) {
        socket.Bind(address);
        socket.Listen(backlog);
    }
  
    Client Accept_client() {
        int new_fd = socket.Accept();
        // Pass the new file descriptor to the client constructor
        return Client(new_fd);
    }
private:
    Socket socket;
};
