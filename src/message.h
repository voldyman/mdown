#pragma once

#include <sstream>

#include <cereal/archives/binary.hpp>
#include <cereal/types/string.hpp>

namespace zmq {
class message_t;
}

template <class Message>
std::string serialize(const Message& message) {
    std::stringstream ss;
    {
        cereal::BinaryOutputArchive archive(ss);
        archive(message);
    }
    return ss.str();
}

template <class Message>
void deserialize(const std::string& data, Message* message) {
    std::stringstream ss(data);
    {
        cereal::BinaryInputArchive archive(ss);
        archive(*message);
    }
}

class PingMessage {
  public:
    explicit PingMessage(std::string msg_str = "Ping");

    void Parse(const zmq::message_t& msg);

    const std::string& data() {
        return data_;
    }

    template <class Archive>
    void serialize(Archive& archive) {
        archive(data_);
    }

  private:
    std::string data_;
};

class PongMessage {
  public:
    explicit PongMessage(std::string msg_str = "Pong");

    void Parse(const zmq::message_t& msg);

    const std::string& data() {
        return data_;
    }

    template <class Archive>
    void serialize(Archive& archive) {
        archive(data_);
    }

  private:
    std::string data_;
};
