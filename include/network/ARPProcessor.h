#ifndef ARP_PROCESSOR_H
#define ARP_PROCESSOR_H

#include "base/PacketProcessor.h"
#include <cstddef>
#include <memory>
#include <netinet/ip.h>

class ARPProcessor : public PacketProcessor {
public:
  void process(const u_int8_t *packet, size_t length,
               std::shared_ptr<PacketContext> context) override;

  std::string get_name() const override { return "ARP"; }

  // Register all IP protocol handlers
  void register_handlers() override { return; };
};

#endif // !ARP_PROCESSOR_H!
