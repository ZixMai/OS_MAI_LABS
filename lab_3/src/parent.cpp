#include <stdexcept>
#include <unistd.h>
#include <sys/wait.h>

#include "utils.h"
#include "consts/Consts.h"
#include "sharedFile/SharedFile.h"
#include "sharedMem/SharedMem.h"
#include "sharedSem/SharedSem.h"

std::string get_file_name(std::istream& stream){
    std::string buff;
    std::getline(stream, buff);
    return buff;
}

int parent_main(std::istream& input, std::ostream& output) {
    auto parentSem = SharedSem(kSemParentName);
    auto childSem = SharedSem(kSemChildName);

    auto childFile = SharedFile(kChildFilename);

    const std::string file_name = get_file_name(input);;
    start_process(file_name);

    auto bufferC2P = SharedMem(childFile.getFd(), 4096);

    float res;
    while (true) {
        childSem.post();
        parentSem.wait();
        res = bufferC2P.buffer[0];
        if (res == .0f) {
            output << "Division by zero" << std::endl;
        }
        if (res == .0f || res == 2.0f) {
            break;
        }
        res = bufferC2P.buffer[1];
        output << res << std::endl;
    }

    wait(nullptr);
    return 0;
}