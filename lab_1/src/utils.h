#pragma once
#include <fstream>
#include <unistd.h>

inline std::ofstream create_file(const std::string&file_name) {
    std::ofstream file;
    file.open(file_name);
    if (!file.good()) {
        throw std::runtime_error("File could not be opened");
    }
    return file;
}

inline bool start_process(const std::string&file_name, int pipeC2P[2]) {
    const pid_t pid = fork();
    if (pid == 0) {
        close(pipeC2P[0]);
        dup2(pipeC2P[1], STDOUT_FILENO);
        if (execl("./lab_1_child_exe", file_name.c_str(), nullptr) == -1) {
            throw std::runtime_error("Exec failed");
        }
    }

    return pid == 0;
}
