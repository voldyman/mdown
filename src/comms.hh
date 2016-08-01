#pragma once

#include <memory>

class Message;

enum class CommsMode { SERVER, CLIENT };

class Comms {
  public:
    Comms(CommsMode mode);

    bool Send(const Message& msg);
    bool Receive(Message* msg);
    bool Wait();
    ~Comms();

  private:
    class Impl;
    std::unique_ptr<Impl> impl_;
};
