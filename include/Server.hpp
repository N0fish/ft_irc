#ifndef SERVER_HPP
#define SERVER_HPP

#include <string>
#include <vector>
#include <map>
#include <poll.h>
#include <netinet/in.h> // For sockaddr_in

class Server {
private:
    int serverSocket;
    int port;
    std::string password;
    struct sockaddr_in serverAddr;
    std::vector<struct pollfd> clients; // List of client file descriptors

    void initSocket();
    void acceptConnection();
    void handleClient(int clientFd);

public:
    Server(int port, const std::string &password);
    ~Server();
    void run();
};

#endif
