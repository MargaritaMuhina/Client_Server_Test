#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <stdexcept>

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        throw std::runtime_error(std::string("socket failed: ") + strerror(errno));
    }
    return res;
}
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        throw std::runtime_error(std::string("bind failed: ") + strerror(errno));
    }
}
void Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        throw std::runtime_error(std::string("listen failed: ") + strerror(errno));
    }
}
int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        throw std::runtime_error(std::string("accept failed: ") + strerror(errno));
    }
    return res;
}
void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        throw std::runtime_error(std::string("connect failed: ") + strerror(errno));
    }
}
void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        throw std::runtime_error("inet_pton failed: src does not contain a character string representing a valid network address in the specified address family");
    }
    if (res == -1) {
        throw std::runtime_error(std::string("inet_pton failed: ") + strerror(errno));
    }
}

