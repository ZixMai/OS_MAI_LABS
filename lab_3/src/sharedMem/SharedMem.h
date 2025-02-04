#pragma once
#include <cstddef>

class SharedMem {
public:
    float* buffer;
    const size_t size;

    SharedMem(int fd, size_t size);

    ~SharedMem();
};
