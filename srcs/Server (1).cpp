#include "Server.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <fcntl.h>
#include <cerrno> // Добавляем этот заголовок

Server::Server(int port, const std::string &password) 
    : port(port), password(password) {
    initSocket();
}

Server::~Server() {
    close(serverSocket);
}

void Server::initSocket() {
    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    // Set socket to non-blocking mode
    int flags = fcntl(serverSocket, F_GETFL, 0);
    if (flags < 0 || fcntl(serverSocket, F_SETFL, flags | O_NONBLOCK) < 0) {
        throw std::runtime_error("Failed to set non-blocking mode");
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        throw std::runtime_error("Bind failed");
    }

    if (listen(serverSocket, 10) < 0) {
        throw std::runtime_error("Listen failed");
    }

    std::cout << "Server started on port " << port << std::endl;
}

void Server::acceptConnection() {
    int clientFd = accept(serverSocket, NULL, NULL);
    if (clientFd < 0) {
        if (errno != EWOULDBLOCK) { // Используем errno и EWOULDBLOCK
            std::cerr << "Accept error" << std::endl;
        }
        return;
    }

    // Add client to poll list
    struct pollfd clientPoll;
    clientPoll.fd = clientFd;
    clientPoll.events = POLLIN;
    clients.push_back(clientPoll);

    std::cout << "New client connected: " << clientFd << std::endl;
}

void Server::handleClient(int clientFd) {
    char buffer[1024];
    memset(buffer, 0, sizeof(buffer));
    ssize_t bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);

    if (bytesRead <= 0) {
        if (bytesRead < 0 && errno != EWOULDBLOCK) { // Используем errno и EWOULDBLOCK
            std::cerr << "Recv error for client " << clientFd << std::endl;
        }
        close(clientFd);
        return;
    }

    std::cout << "Received from client " << clientFd << ": " << buffer << std::endl;

    // Echo the message back
    send(clientFd, buffer, bytesRead, 0);
}

void Server::run() {
    struct pollfd serverPoll;
    serverPoll.fd = serverSocket;
    serverPoll.events = POLLIN;

    clients.push_back(serverPoll);

    while (true) {
        int pollCount = poll(clients.data(), clients.size(), -1);
        if (pollCount < 0) {
            throw std::runtime_error("Poll failed");
        }

        for (size_t i = 0; i < clients.size(); ++i) {
            if (clients[i].revents & POLLIN) {
                if (clients[i].fd == serverSocket) {
                    acceptConnection();
                } else {
                    handleClient(clients[i].fd);
                }
            }
        }
    }
}
