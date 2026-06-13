#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <limits>

inline int readInt() {
    int val;
    while (!(std::cin >> val)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "输入无效，请重新输入: ";
    }
    return val;
}

inline double readDouble() {
    double val;
    while (!(std::cin >> val)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "输入无效，请重新输入: ";
    }
    return val;
}

#endif
