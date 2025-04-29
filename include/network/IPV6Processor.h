#ifndef IPV6_PROCESSOR_H
#define IPV6_PROCESSOR_H

#include "base/PacketProcessor.h"
#include <cstddef>
#include <memory>
#include <netinet/ip.h>

class IPV6Processor : public PacketProcessor {
public:
  void process(const u_int8_t *packet, size_t length,
               std::shared_ptr<PacketContext> context) override;

  std::string get_name() const override { return "IPv6"; }

  // Register all IP protocol handlers
  void register_handlers() override;
};

#endif // IPV6_PROCESSOR_H!
