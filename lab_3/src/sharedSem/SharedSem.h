#pragma once
#include <string>
#include <semaphore.h>

class SharedSem {
private:
    sem_t* sem_;
    const std::string name_;
public:
    explicit SharedSem(std::string name);

    void wait();

    void post();

    ~SharedSem();
};

