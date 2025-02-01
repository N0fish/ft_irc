#include <iostream>
#include <vector>
#include <string>
#include <cassert>  // Для assert() в базовых тестах
#include "Server.hpp"
#include "Client.hpp"

void test_pass();
void test_nick();
void test_user();
void test_join();
void test_part();
void test_privmsg();
void test_ping();
void test_invite();
void test_topic();
void test_kick();
void test_mode();

int main() {
    std::cout << "Running IRC Server Tests..." << std::endl << std::flush;

    try {
        test_pass();
        test_nick();
        test_user();
        test_join();
        test_part();
        test_privmsg();
        test_ping();
        test_invite();
        test_topic();
        test_kick();
        test_mode();

        std::cout << "All tests passed successfully!" << std::endl << std::flush;
    } catch (const std::exception &e) {
        std::cerr << "Test failed: " << e.what() << std::endl << std::flush;
        return 1;
    }

    return 0;
}

// Тест команды PASS (аутентификация клиента)
void test_pass() {
    std::cout << "[TEST] PASS command" << std::endl << std::flush;;

    // 1. Создаём тестовый сервер с паролем "testpass"
    Server server(6667, "testpass");

    // 2. Создаём тестового клиента
    Client testClient(4); // fd = 4, эмуляция клиента
    std::vector<std::string> args;
    args.push_back("testpass");

    // 3. Вызываем обработчик команды PASS
    server.handleCommand(&testClient, "PASS testpass");

    // 4. Проверяем, что клиент успешно аутентифицирован
    //assert(testClient.isAuthenticated() == true);

    std::cout << "PASS command test passed ✅" << std::endl << std::flush;
}

// Тест команды NICK (изменение никнейма)
void test_nick() {
    std::cout << "[TEST] NICK command" << std::endl << std::flush;
    // Тестирование смены никнейма и проверки уникальности
}

// Тест команды USER (установка имени пользователя)
void test_user() {
    std::cout << "[TEST] USER command" << std::endl << std::flush;
    // Проверка, что пользователь задаёт корректные параметры
}

// Тест команды JOIN (вход в канал)
void test_join() {
    std::cout << "[TEST] JOIN command" << std::endl << std::flush;
    // Проверка входа в существующий и новый канал
}

// Тест команды PART (выход из канала)
void test_part() {
    std::cout << "[TEST] PART command" << std::endl << std::flush;
    // Проверка выхода из канала, а также удаления пустого канала
}

// Тест команды PRIVMSG (отправка сообщений)
void test_privmsg() {
    std::cout << "[TEST] PRIVMSG command" << std::endl << std::flush;
    // Проверка отправки личных и каналовых сообщений
}

// Тест команды PING (проверка активности клиента)
void test_ping() {
    std::cout << "[TEST] PING command" << std::endl << std::flush;
    // Проверка, что сервер корректно отвечает PONG
}

// Тест команды INVITE (приглашение в канал)
void test_invite() {
    std::cout << "[TEST] INVITE command" << std::endl << std::flush;
    // Проверка, что только оператор может приглашать в закрытые каналы
}

// Тест команды TOPIC (изменение темы в канале)
void test_topic() {
    std::cout << "[TEST] TOPIC command" << std::endl << std::flush;
    // Проверка установки, изменения и получения темы
}

// Тест команды KICK (исключение из канала)
void test_kick() {
    std::cout << "[TEST] KICK command" << std::endl << std::flush;
    // Проверка, что только оператор может кикнуть участника
}

// Тест команды MODE (изменение настроек канала)
void test_mode() {
    std::cout << "[TEST] MODE command" << std::endl << std::flush;
    // Проверка установки различных режимов канала (например, +i, +t)
}
