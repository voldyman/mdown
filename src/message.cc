#include "message.h"

#include <cppzmq/zmq.hpp>


// PingMessage Impl begin

PingMessage::PingMessage(std::string msg_str) : data_{msg_str} {}

// PingMessage Impl end

// PongMessage Impl begin

PongMessage::PongMessage(std::string msg_str) : data_{msg_str} {}

// PongMessage Impl end
