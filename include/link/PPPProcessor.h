#ifndef PPP_PROCESSOR_H
#define PPP_PROCESSOR_H

#include "Protocols.h"
#include "base/PacketProcessor.h"
#include <cstddef>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <memory>
#include <netinet/ether.h>

class PPPProcessor : public PacketProcessor {
public:
  void process(const u_int8_t *packet, size_t length,
               std::shared_ptr<PacketContext> context) override;

  std::string get_name() const override { return "Ethernet"; }

  // Print ethernet header
  void print_header(const struct eth_hdr *ethernet);

  // Register all proctocol handlers
  void register_handlers() override;
};

#endif // !PPP_PROCESSOR_H
