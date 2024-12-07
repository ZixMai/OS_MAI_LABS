#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <unistd.h>
#include <vector>

int main(int argc, char *argv[]) {
    if (argc != 1) {
        throw std::invalid_argument("Wrong number of arguments");
    }

    int fd = open(argv[0], O_RDONLY);
    dup2(fd, STDIN_FILENO);
    constexpr float zero = 0.0f;
    constexpr float one = 1.0f;
    constexpr float two = 2.0f;


    std::string line;
    while (std::getline(std::cin, line)) {
        std::istringstream iss(line);
        std::vector<float> numbers;
        float num;

        while (iss >> num) {
            numbers.push_back(num);
        }

        const float first = numbers.front();
        if (std::find(numbers.begin() + 1, numbers.end(), 0.0f) != numbers.end()) {
            write(STDOUT_FILENO, &zero, sizeof(float));
            write(STDOUT_FILENO, &zero, sizeof(float));
            break;
        }

        float result = first;
        for (size_t i = 1; i < numbers.size(); ++i) {
            result /= numbers[i];
        }

        write(STDOUT_FILENO, &one, sizeof(float));
        write(STDOUT_FILENO, &result, sizeof(float));
    }
    write(STDOUT_FILENO, &two, sizeof(float));
    close(fd);
    return 0;
}
