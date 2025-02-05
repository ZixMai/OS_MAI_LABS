#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include <vector>

#include "consts/Consts.h"
#include "sharedFile/SharedFile.h"
#include "sharedMem/SharedMem.h"
#include "sharedSem/SharedSem.h"

int main(int argc, char *argv[]) {
    if (argc != 1) {
        throw std::invalid_argument("Wrong number of arguments");
    }

    int fd = open(argv[0], O_RDONLY);
    dup2(fd, STDIN_FILENO);
    constexpr float zero = 0.0f;
    constexpr float one = 1.0f;
    constexpr float two = 2.0f;

    auto parentSem = SharedSem(kSemParentName);
    auto childSem = SharedSem(kSemChildName);

    auto childFile = SharedFile(kChildFilename);

    auto bufferC2P = SharedMem(childFile.getFd(), 4096);

    std::string line;
    while (true) {
        childSem.wait();

        if (!std::getline(std::cin, line)) {
            break;
        }

        std::istringstream iss(line);
        std::vector<float> numbers;
        float num;

        while (iss >> num) {
            numbers.push_back(num);
        }

        const float first = numbers.front();
        if (std::find(numbers.begin() + 1, numbers.end(), 0.0f) != numbers.end()) {
            bufferC2P.buffer[0] = zero;
            bufferC2P.buffer[1] = zero;
            break;
        }

        float result = first;
        for (size_t i = 1; i < numbers.size(); ++i) {
            result /= numbers[i];
        }

        bufferC2P.buffer[0] = one;
        bufferC2P.buffer[1] = result;

        parentSem.post();
    }
    if (bufferC2P.buffer[0] != zero) {
        bufferC2P.buffer[0] = two;
    }
    close(fd);
    parentSem.post();
    return 0;
}
