#include "SharedMem.h"
#include <sys/mman.h>


SharedMem::SharedMem(int fd, size_t size) : size(size) {
    buffer = static_cast<float*>(mmap(nullptr, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0));
}

SharedMem::~SharedMem() {
    munmap(buffer, size);
}
