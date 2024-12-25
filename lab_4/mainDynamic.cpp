#include <functional>
#include <istream>
#include <iostream>
#include <dlfcn.h>

const inline std::string pathToF1 = "./libf1.so";
const inline std::string pathToF2 = "./libf2.so";

using GcdFuncPointer = int (*)(int a, int b);
using PiFuncPointer = float (*)(int a);

using GcdHandler = std::function<int (int, int)>;
using PiFunc = std::function<float (int)>;

void handlePi(const PiFunc& CalcPi) {
    int n;

    std::cout << "Enter n: ";
    std::cin >> n;

    auto result = CalcPi(n);
    std::cout << "Result: " << result << std::endl;
}

void handleGcd(const GcdHandler& GcdFunction) {
    int a, b;

    std::cout << "Enter 2 numbers separated by space: ";
    std::cin >> a >> b;

    auto result = GcdFunction(a, b);
    std::cout << "Result: " << result << std::endl;;
}


void handleGcdDynamic(void* libHandle, const std::string& funcName) {
    auto pi = reinterpret_cast<GcdFuncPointer>(dlsym(libHandle, funcName.c_str()));

    if (!pi) {
        std::cout << "Error while loading library: Can't use function " << funcName << std::endl;
        return;
    }

    handleGcd(pi);
}


void handlePiDynamic(void* libHandle, const std::string& funcName) {
    auto pi = reinterpret_cast<PiFuncPointer>(dlsym(libHandle, funcName.c_str()));

    if (!pi) {
        std::cout << "Error while loading library: Can't use function " << funcName << std::endl;
        return;
    }

    handlePi(pi);
}

void* loadLib(const std::string& path){
    void* libHandle = dlopen(path.c_str(), RTLD_LAZY);
    if (!libHandle) {
        std::cout << "Error while loading library: " << dlerror() << std::endl;
        return nullptr;
    }
    return libHandle;
}

int main(int argv, char** argc){
    auto command = 0;

    auto libHandle = dlopen(pathToF1.c_str(), RTLD_LAZY);
    auto isF1 = true;
    
    while (command != 5) {
        std::cout << "Enter command: ";
        std::cin >> command;

        switch (command) {
            case 0:
                if (isF1) {
                    libHandle = loadLib(pathToF2);
                    isF1 = false;
                }
                else {
                    libHandle = loadLib(pathToF1);
                    isF1 = true;
                }
                break;
            case 1:
                handleGcdDynamic(libHandle, isF1 ? "EuclidGcd" : "StandardGcd");
            break;
            case 2:
                handlePiDynamic(libHandle, isF1 ? "PiVallis" : "PiLeibniz");
                break;
            default:
                break;
        }

        if (command == 3) return 0;
    }
}