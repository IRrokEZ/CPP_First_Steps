#include <iostream>

void PrintText () {
    std::cout << "C++ is a general-purpose programming language with a "
              << "bias towards systems programming that" << "\n"
              << "  - is a better C" << "\n"
              << "  - supports data abstraction" << "\n"
              << "  - supports object-oriented programming" << "\n"
              << "  - supports generic programming." << "\n";
}

void Summ () {
    int a, b;
    std::cin >> a >> b;
    std::cout << a + b;
}

int main() {
    Summ();
    return 0;
}
