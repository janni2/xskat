#ifndef IRCCLIENT_H
#define IRCCLIENT_H

#include <string>
#include <functional>

namespace Application {

class IrcClient {
public:
    IrcClient();
    ~IrcClient();

    void connect(const std::string& server, int port, const std::string& nick, const std::string& channel);
    void disconnect();
    void sendMessage(const std::string& message);

    // Handlers for received messages, to be set by the GameController
    std::function<void(const std::string& from, const std::string& message)> onPrivateMessage;
    std::function<void(const std::string& command, const std::string& args)> onGameCommand;

    void processMessages();

private:
    int socket_fd;
    std::string server;
    int port;
    std::string nick;
    std::string channel;
    bool connected;

    void sendRaw(const std::string& rawMessage);
    void parseMessage(const std::string& message);
};

} // namespace Application

#endif // IRCCLIENT_H