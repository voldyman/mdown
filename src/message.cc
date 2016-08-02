#include "message.hh"

#include <cppzmq/zmq.hpp>


// PingMessage Impl begin

PingMessage::PingMessage(std::string msg_str) : data_{msg_str} {}

void PingMessage::Parse(const zmq::message_t& msg) {
    auto cstr = static_cast<const char*>(msg.data());
    data_ = std::string(cstr, msg.size());
}

// PingMessage Impl end

// PongMessage Impl begin

PongMessage::PongMessage(std::string msg_str) : data_{msg_str} {}

void PongMessage::Parse(const zmq::message_t& msg) {
    auto cstr = static_cast<const char*>(msg.data());
    data_ = std::string(cstr, msg.size());
}

// PongMessage Impl end
