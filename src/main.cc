#include <cstdio>
#include <functional>
#include <iostream>
#include <stdexcept>
#include <unistd.h>

#include "cppzmq/zmq.hpp"
#include "gflags/gflags.h"

DEFINE_bool(start, false, "Should start daemon");
namespace {

void SetupDaemon() {
    setsid();
}

void StartDaemon(std::function<void(void)> daemon_func, bool wait_for_exit = false) {
    pid_t pid = fork();

    if (pid < 0) {
        throw std::runtime_error("Coudln't daemonize");

    } else if (pid > 0) {
        if (wait_for_exit) {
            waitpid(pid, nullptr, 0);
        }
    } else {
        // child process
        SetupDaemon();
        daemon_func();
        exit(0);
    }
}

void zmq_server() {
    zmq::context_t ctx;
    zmq::socket_t socket{ctx, zmq::socket_type::pair};
    socket.bind("tcp://*:2221");

    std::string message_str = "This is a test, don't panic";
    zmq::message_t msg{message_str.begin(), message_str.end()};

    socket.send(msg);
}

void zmq_client() {
    zmq::context_t ctx;
    zmq::socket_t socket{ctx, zmq::socket_type::pair};
    socket.connect("tcp://localhost:2221");

    zmq::message_t msg{};

    socket.recv(&msg);

    std::cout << static_cast<char*>(msg.data()) << std::endl;
}


} // namespace
int main(int argc, char* argv[]) {
    gflags::SetVersionString("0.1");
    gflags::SetUsageMessage("mDown is a download manager front end");
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    if (FLAGS_start) {
        std::cout << "starting" << std::endl;
    }
    try {
        StartDaemon([]() {
            zmq_server();
            std::cout << "Test" << std::endl;
        });
    } catch (std::exception& ex) {
        std::cout << "Failed to start because " << ex.what() << std::endl;
    }
    zmq_client();
    return 0;
}
