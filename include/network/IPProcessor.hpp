#ifndef IP_PROCESSOR_H
#define IP_PROCESSOR_H

#include "base/PacketProcessor.hpp"
#include <cstddef>
#include <memory>
#include <netinet/ip.h>

class IPProcessor : public PacketProcessor {
public:
  void process(const u_int8_t *packet, size_t length,
               std::shared_ptr<PacketContext> context) override;

  std::string get_name() const override { return "IPv4"; }

  // Register all IP protocol handlers
  void register_handlers() override;
};

#endif // !IP_PROCESSOR_H
