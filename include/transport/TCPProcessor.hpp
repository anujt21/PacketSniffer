#ifndef TCP_PROCESSOR_H
#define TCP_PROCESSOR_H

#include "base/PacketProcessor.hpp"
#include <cstddef>
#include <memory>
#include <sys/types.h>

class TCPProcessor : public PacketProcessor {
public:
  void process(const u_int8_t *packet, size_t length,
               std::shared_ptr<PacketContext> context) override;

  std::string get_name() const override { return "TCP"; }

  void register_handlers() override;
};

#endif // !DEBUG
