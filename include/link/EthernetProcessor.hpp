#ifndef ETHERNET_PROCESSOR_H
#define ETHERNET_PROCESSOR_H

#include "base/PacketProcessor.hpp"
#include <cstddef>
#include <memory>
#include <netinet/ether.h>

class EthernetProcessor : public PacketProcessor {
public:
  void process(const u_int8_t *packet, size_t length,
               std::shared_ptr<PacketContext> context) override;

  std::string get_name() const override { return "Ethernet"; }

  // Register all proctocol handlers
  void register_handlers() override;
};

#endif // !ETHERNET_PROCESSOR_H
