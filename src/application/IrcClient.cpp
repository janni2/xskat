#include "IrcClient.h"
#include <iostream>
#include <stdexcept>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <fcntl.h>

namespace Application {

IrcClient::IrcClient() : socket_fd(-1), port(0), connected(false) {}

IrcClient::~IrcClient() {
    if (connected) {
        disconnect();
    }
}

void IrcClient::connect(const std::string& server, int port, const std::string& nick, const std::string& channel) {
    this->server = server;
    this->port = port;
    this->nick = nick;
    this->channel = channel;

    // TODO: A full socket implementation would go here.
    // This is a simplified placeholder.
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        throw std::runtime_error("Failed to create socket.");
    }

    // For now, we'll just log that we would connect.
    std::cout << "Connecting to IRC server " << server << ":" << port << " with nick " << nick << std::endl;

    // Placeholder for sending USER and NICK commands
    // sendRaw("NICK " + nick);
    // sendRaw("USER " + nick + " 0 * :" + nick);

    connected = true; // Assume connection is successful for now.
}

void IrcClient::disconnect() {
    if (connected) {
        // sendRaw("QUIT :Leaving");
        close(socket_fd);
        socket_fd = -1;
        connected = false;
        std::cout << "Disconnected from IRC server." << std::endl;
    }
}

void IrcClient::sendMessage(const std::string& message) {
    if (connected) {
        // sendRaw("PRIVMSG " + channel + " :" + message);
    }
}

void IrcClient::sendRaw(const std::string& rawMessage) {
    if (socket_fd != -1) {
        std::string fullMessage = rawMessage + "\r\n";
        // send(socket_fd, fullMessage.c_str(), fullMessage.length(), 0);
    }
}

void IrcClient::processMessages() {
    if (!connected) return;

    // TODO: Implement non-blocking read from socket and message parsing.
    // char buffer[4096];
    // int bytes_received = recv(socket_fd, buffer, sizeof(buffer) - 1, 0);
    // if (bytes_received > 0) {
    //     buffer[bytes_received] = '\0';
    //     std::string received(buffer);
    //     // Process and parse 'received' string line by line
    // }
}

void IrcClient::parseMessage(const std::string& message) {
    // TODO: Implement IRC message parsing to identify commands (PRIVMSG, PING, etc.)
    // and call the appropriate handlers (onPrivateMessage, onGameCommand).
    // e.g., if (message is a PING) sendRaw("PONG ...")
}

} // namespace Application