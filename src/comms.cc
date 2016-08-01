#include "comms.hh"

#include <array>

#include "cppzmq/zmq.hpp"
#include "message.hh"

const int PORT = 2211;

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

    bool Send(const Message& message) {
        return socket_.send(message.GetZMQMessage());
    }

    bool Receive(Message* message) {
        zmq::message_t msg;
        if (socket_.recv(&msg)) {
            message->Parse(msg);
            return true;
        } else {
            return false;
        }
    }

    bool Wait() {
        using std::chrono::milliseconds;
        std::array<zmq::pollitem_t, 1> items = {{socket_, /* fd */ 0, ZMQ_POLLIN, /* revents */ 0}};
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

bool Comms::Send(const Message& msg) {
    return impl_->Send(msg);
}

bool Comms::Receive(Message* msg) {
    return impl_->Receive(msg);
}

bool Comms::Wait() {
    return impl_->Wait();
}

Comms::~Comms() {}
