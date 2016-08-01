#include "message.hh"

#include "cppzmq/zmq.hpp"

Message::~Message() {}

// PingMessage Impl begin

PingMessage::PingMessage(std::string msg_str) : data_{msg_str} {}

zmq::message_t PingMessage::GetZMQMessage() const {
    return zmq::message_t{data_.begin(), data_.end()};
}

void PingMessage::Parse(const zmq::message_t& msg) {
    data_ = static_cast<const char*>(msg.data());
    data_.resize(msg.size());
}

// PingMessage Impl end

// PongMessage Impl begin

PongMessage::PongMessage(std::string msg_str) : data_{msg_str} {}

zmq::message_t PongMessage::GetZMQMessage() const {
    return zmq::message_t{data_.begin(), data_.end()};
}

void PongMessage::Parse(const zmq::message_t& msg) {
    data_ = static_cast<const char*>(msg.data());
}

// PongMessage Impl end
