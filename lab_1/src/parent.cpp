#include <iostream>
#include <stdexcept>
#include <unistd.h>
#include "utils.h"

std::string get_file_name(std::istream& stream){
    std::string buff;
    std::getline(stream, buff);
    return buff;
}

int parent_main(std::istream& input, std::ostream& output) {
    int pipeC2P[2];
    if (pipe(pipeC2P) == -1) {
        throw std::runtime_error("Pipe could not be created");
    }

    const std::string file_name = get_file_name(input);;
    start_process(file_name, pipeC2P);

    float res;
    while (true) {
        read(pipeC2P[0], &res, sizeof(res));
        if (res == .0f) {
            output << "Division by zero" << std::endl;
        }
        if (res == .0f || res == 2.0f) {
            break;
        }
        read(pipeC2P[0], &res, sizeof(res));
        output << res << std::endl;
    }

    close(pipeC2P[0]);
    close(pipeC2P[1]);

    return 0;
}