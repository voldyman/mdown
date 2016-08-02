#include <functional>
#include <iostream>
#include <unistd.h>

#include <gflags/gflags.h>

#include "comms.hh"
#include "message.hh"

namespace {

DEFINE_bool(start, false, "Should start daemon");

void SetupDaemon() {
    setsid();

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
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
    Comms comm(CommsMode::SERVER);

    PingMessage ping("ping from daemon");
    comm.Send(serialize(ping));
}

void zmq_client() {
    Comms comm(CommsMode::CLIENT);

    std::string raw_message;
    comm.Receive(&raw_message);

    PingMessage pong_message;
    deserialize(raw_message, &pong_message);

    std::cout << pong_message.data() << std::endl;
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
        StartDaemon([]() { zmq_server(); });
    } catch (std::exception& ex) {
        std::cout << "Failed to start because " << ex.what() << std::endl;
    }
    zmq_client();
    return 0;
}
