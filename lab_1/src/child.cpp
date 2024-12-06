#include <fcntl.h>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc != 1) {
        throw std::invalid_argument("Wrong number of arguments");
    }

    int fd = open(argv[0], O_RDONLY);
    dup2(fd, STDIN_FILENO);
    float n1, n2, n3;
    constexpr float zero = 0.0f;
    constexpr float one = 1.0f;
    constexpr float two = 2.0f;

    while (std::cin >> n1 >> n2 >> n3) {
        if (n2 == 0 || n3 == 0) {
            write(STDOUT_FILENO, &zero, sizeof(float));
            write(STDOUT_FILENO, &zero, sizeof(float));
            break;
        }
        float res = n1 / n2 / n3;
        write(STDOUT_FILENO, &one, sizeof(float));
        write(STDOUT_FILENO, &res, sizeof(float));
    }
    write(STDOUT_FILENO, &two, sizeof(float));
    close(fd);
    return 0;
}