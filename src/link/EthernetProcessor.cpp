#include "link/EthernetProcessor.h"
#include "Protocols.h"
#include "base/ProtocolRegistry.h"
#include "network/IPProcessor.h"
#include <cstddef>
#include <memory>

void EthernetProcessor::process(const u_int8_t *packet, size_t length,
                                std::shared_ptr<PacketContext> context) {
  if (length < SIZE_ETHERNET) {
    std::cerr << "Packet size smaller than ethernet header." << std::endl;
  }
  const struct eth_hdr *ethernet;

  ethernet = (struct eth_hdr *)(packet);
  u_short ether_type = ntohs(ethernet->ether_type);

  if (context->verbose) {
  }

  const u_int8_t *payload = packet + SIZE_ETHERNET;
  size_t payload_length = length - SIZE_ETHERNET;

  auto &registry = ProtocolRegistry::get_instance();
  auto network_processor = registry.get_network_processor(ether_type);

  if (network_processor) {
    network_processor->register_handlers();
    network_processor->process(payload, payload_length, context);
  } else {
    std::cerr << "No network processor found for network type: " << ether_type
              << std::endl;
  }
}

// Register all network handlers corersponding to ethernet
void EthernetProcessor::register_handlers() {
  auto &registry = ProtocolRegistry::get_instance();
  registry.register_network(ETHERTYPE_IP, std::make_shared<IPProcessor>());
}
