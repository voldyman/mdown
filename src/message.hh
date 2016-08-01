#pragma once

#include "string"

namespace zmq {
class message_t;
}

class Message {
  public:
    virtual zmq::message_t GetZMQMessage() const = 0;
    virtual void Parse(const zmq::message_t& msg) = 0;

    virtual ~Message() = 0;
};

class PingMessage : public Message {
  public:
    PingMessage(std::string msg_str = "Ping");

    zmq::message_t GetZMQMessage() const override;
    void Parse(const zmq::message_t& msg) override;

    const std::string& data() {
        return data_;
    }

  private:
    std::string data_;
};

class PongMessage : public Message {
  public:
    PongMessage(std::string msg_str = "Pong");

    zmq::message_t GetZMQMessage() const override;
    void Parse(const zmq::message_t& msg) override;

    const std::string& data() {
        return data_;
    }

  private:
    std::string data_;
};
