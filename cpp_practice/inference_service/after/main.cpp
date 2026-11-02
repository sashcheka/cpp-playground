#include "inference.hpp"

#include <exception>
#include <iostream>

int main() {
    try {
        CsvParser parser;
        MaxModel model;
        Logger logger(std::clog);
        InferenceServer server(model, parser, logger);

        std::cout << server.Predict("1, 2, 3") << '\n';
        std::cout << server.Predict("1, hello, 3") << '\n';
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
}
