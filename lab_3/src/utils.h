#pragma once
#include <fstream>
#include <unistd.h>
#include <vector>

inline std::ofstream create_file(const std::string&file_name) {
    std::ofstream file;
    file.open(file_name);
    if (!file.good()) {
        throw std::runtime_error("File could not be opened");
    }
    return file;
}

inline bool start_process(const std::string&file_name) {
    const pid_t pid = fork();
    if (pid == 0) {
        if (execl("./lab_3_child_exe", file_name.c_str(), nullptr) == -1) {
            throw std::runtime_error("Exec failed");
        }
    }

    return pid == 0;
}

inline std::vector<std::string> read_file(std::ifstream & in) {
    std::vector<std::string> result;
    std::string buffer;

    while (std::getline(in, buffer)) {
        result.push_back(buffer);
    }

    return result;
}

inline bool check_equals_of_strings(const std::vector<std::string> & current, const std::vector<std::string> & expected) {
    if (current.size() != expected.size()) {
        return false;
    }

    for (int i = 0; i < current.size(); i++) {
        if (current[i] != expected[i]) {
            return false;
        }
    }

    return true;
}
