#include <string>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>

class Channel {
private:
    std::string name;
    std::string topic;
    std::string password;
    int userLimit = 0;
    bool inviteOnly = false;
    std::set<std::string> operators;
    std::set<std::string> invitedUsers;
    std::map<std::string, std::string> participants; // username -> userInfo

public:
    Channel(const std::string& channelName) : name(channelName) {}

    // Добавить участника
    bool addParticipant(const std::string& username, const std::string& userInfo) {
        if (userLimit > 0 && participants.size() >= userLimit) {
            std::cerr << "Channel is full!\n";
            return false;
        }
        if (inviteOnly && invitedUsers.find(username) == invitedUsers.end()) {
            std::cerr << "User is not invited!\n";
            return false;
        }
        participants[username] = userInfo;
        return true;
    }

    // Удалить участника
    bool removeParticipant(const std::string& username) {
        return participants.erase(username) > 0;
    }

    // Назначить оператора
    void addOperator(const std::string& username) {
        if (participants.find(username) != participants.end()) {
            operators.insert(username);
        }
    }

    // Убрать оператора
    void removeOperator(const std::string& username) {
        operators.erase(username);
    }

    // Установить тему
    void setTopic(const std::string& newTopic, const std::string& username) {
        if (inviteOnly && operators.find(username) == operators.end()) {
            std::cerr << "Only operators can set the topic!\n";
            return;
        }
        topic = newTopic;
    }

    // Получить тему
    std::string getTopic() const {
        return topic;
    }

    // Установить режим
    void setMode(char mode, const std::string& value = "") {
        switch (mode) {
            case 'i': // Только по приглашению
                inviteOnly = !inviteOnly;
                break;
            case 't': // Установка ограничений на тему
                // Здесь можно реализовать логику ограничения темы только для операторов
                break;
            case 'k': // Установка пароля
                password = value;
                break;
            case 'l': // Лимит участников
                userLimit = std::stoi(value);
                break;
            default:
                std::cerr << "Invalid mode!\n";
        }
    }

    // Приглашение пользователя
    void invite(const std::string& username) {
        invitedUsers.insert(username);
    }

    // Выгнать участника
    bool kick(const std::string& username, const std::string& operatorName) {
        if (operators.find(operatorName) == operators.end()) {
            std::cerr << "Only operators can kick users!\n";
            return false;
        }
        return removeParticipant(username);
    }

    // Проверить является ли пользователь оператором
    bool isOperator(const std::string& username) const {
        return operators.find(username) != operators.end();
    }

    // Получить список участников
    std::vector<std::string> getParticipants() const {
        std::vector<std::string> users;
        for (const auto& [username, _] : participants) {
            users.push_back(username);
        }
        return users;
    }
};
Этот класс включает:

Управление участниками (addParticipant, removeParticipant).
Управление операторами (addOperator, removeOperator).
Команды операторов:
KICK (удаление участника),
INVITE (приглашение в закрытый канал),
TOPIC (установка и просмотр темы),
MODE (настройка режимов канала, таких как пароль, лимит участников и режим только по приглашению).
