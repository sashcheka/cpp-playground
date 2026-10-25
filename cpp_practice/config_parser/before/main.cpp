#include "config.hpp"

#include <iostream>

int main() {
    const auto config = ParseConfig(
        "# Server configuration\n"
        "host = localhost\n"
        "port = 8080\n"
        "port = 9090\n"
        "token = abc=xyz\n"
    );

    std::cout << "Host: " << config.Get("host").value_or("unknown") << '\n';
    std::cout << "Port: " << config.GetInt("port", 80) << '\n';
    std::cout << "Workers: " << config.GetInt("workers", 4) << '\n';
    std::cout << "Token: " << config.Get("token").value_or("") << '\n';
    std::cout << "Keys: " << config.Size() << '\n';
}
