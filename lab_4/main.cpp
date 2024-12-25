#include <istream>
#include <iostream>
#include <functional>
#include "src/f1.h"
#include "src/f2.h"

using GcdHandler = std::function<int (int, int)>;
using PiFunc = std::function<float (int)>;

void handleGcd(const GcdHandler& GcdFunction, std::istream& is, std::ostream& os){
    int a, b;

    os << "Enter 2 numbers separated by space: ";
    is >> a >> b;

    auto result = GcdFunction(a, b);
    os << "Result: " << result << std::endl;;
}

void handlePi(const PiFunc& CalcPi, std::istream& is, std::ostream& os){
    int n;

    os << "Enter n: ";
    is >> n;

    auto result = CalcPi(n);
    os << "Result: " << result << std::endl;
}

int main(int argv, char** argc) {
    int command = 0;
    std::istream& is = std::cin;
    std::ostream& os = std::cout;
    while (command != 5) {
        os << "Enter command: ";
        is >> command;

        switch (command) {
            case 1:
                handleGcd(GcdEuclid, is, os);
                break;
            case 2:
                handleGcd(Gcd, is, os);
                break;
            case 3:
                handlePi(PiLeibniz, is, os);
                break;
            case 4:
                handlePi(PiVallis, is, os);
                break;
            default:
                break;
        }

        if (command == 5) return 0;
    }
}
