#include "base/PacketProcessor.hpp"
#include "Protocols.h"
#include "base/ProtocolRegistry.hpp"
#include "link/EthernetProcessor.hpp"
#include "network/IPProcessor.hpp"
#include <memory>
#include <net/ethernet.h>

void packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr,
                    const u_char *packet) {

  auto packet_context_ptr = reinterpret_cast<PacketContext *>(user_data);
  std::shared_ptr<PacketContext> context(packet_context_ptr,
                                         [](PacketContext *) {});

  context->packet_count++;

  auto &registry = ProtocolRegistry::get_instance();
  auto link_processor = registry.get_link_processor(context->link_type);

  if (link_processor) {
    link_processor->register_handlers();
    link_processor->process(packet, pkthdr->len, context);
  } else {
    std::cerr << "Ethernet processor not found" << std::endl;
  }
}
