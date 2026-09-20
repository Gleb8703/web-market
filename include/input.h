#pragma once
#include <iostream>
#include <string>

inline int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(1000, '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Это не число, попробуй снова\n";
    }
}

inline double readDouble(const std::string& prompt) {
    double value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(1000, '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "Это не число, попробуй снова\n";
    }
}

inline std::string readString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        if (!value.empty()) {
            return value;
        }
        std::cout << "Пустая строка, попробуй снова\n";
    }
}