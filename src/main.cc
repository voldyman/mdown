#include <cstdio>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

namespace {

void SetupDaemon() {
    setsid();
}

} // namespace

void StartDaemon(std::function<void(void)> daemon_func) {
    pid_t pid = fork();

    if (pid < 0) {
        throw std::runtime_error("Coudln't daemonize");

    } else if (pid > 0) {
        waitpid(pid, nullptr, 0); // wait for child to exit

    } else {
        // child process
        SetupDaemon();
        daemon_func();
        exit(0);
    }
}

int main() {
    try {
        StartDaemon([]() { std::cout << "Test" << std::endl; });
    } catch (std::exception& ex) {
        std::cout << "Failed to start because " << ex.what() << std::endl;
    }
    return 0;
}
