#include "comms.h"

#include <array>

#include <cppzmq/zmq.hpp>
#include <message.h>

const int PORT = 2211;

namespace {
// static
zmq::message_t ZmqMessageFromString(const std::string& str) {
    return zmq::message_t{str.data(), str.size()};
}

// static
std::string StringFromZmqMessage(const zmq::message_t& message) {
    const char* data = static_cast<const char*>(message.data());
    return std::string(data, message.size());
}
} // namespace

class Comms::Impl {
  public:
    Impl(CommsMode mode) : mode_{mode}, socket_{ctx_, zmq::socket_type::pair} {
        switch (mode_) {
            case CommsMode::SERVER: {
                socket_.bind("tcp://*:" + std::to_string(PORT));
            } break;
            case CommsMode::CLIENT: {
                socket_.connect("tcp://localhost:" + std::to_string(PORT));
            } break;
        }
    }

    bool Send(const std::string& message) {
        return socket_.send(ZmqMessageFromString(message));
    }

    bool Receive(std::string* message) {
        zmq::message_t msg;
        if (socket_.recv(&msg)) {
            *message = StringFromZmqMessage(msg);
            return true;
        } else {
            return false;
        }
    }

    bool Wait() {
        using std::chrono::milliseconds;
        std::array<zmq::pollitem_t, 1> items = {{socket_, 0 /* fd */, ZMQ_POLLIN, 0 /* revents */}};
        int val = zmq::poll(items.data(), items.size(), milliseconds(3));
        if (val < 0) {
            // handle error condition ?
            return false;
        } else if (val == 0) {
            return false;
        } else {
            return true;
        }
    }

  private:
    CommsMode mode_;
    zmq::context_t ctx_;
    zmq::socket_t socket_;
};

Comms::Comms(CommsMode mode) : impl_{std::make_unique<Impl>(mode)} {}

bool Comms::Send(const std::string& msg) {
    return impl_->Send(msg);
}

bool Comms::Receive(std::string* msg) {
    return impl_->Receive(msg);
}

bool Comms::Wait() {
    return impl_->Wait();
}

Comms::~Comms() {}
