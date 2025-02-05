#pragma once
#include <string>

class SharedFile {
private:
    int fd_;
    const std::string name_;
public:
    explicit SharedFile(std::string name);

    int getFd() const;

    ~SharedFile();
};

