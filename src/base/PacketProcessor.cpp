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

  auto &registry = ProtocolRegistry::getInstance();
  auto ethernet_processor = registry.getEtherTypeProcessor(context->etherType);

  if (ethernet_processor) {
    ethernet_processor->process(packet, pkthdr->len, context);
  }
}

void EthernetProcessor::registerAllHandlers() {
  auto &registry = ProtocolRegistry::getInstance();

  registry.registerEtherType(ETHERTYPE_IP, std::make_shared<IPProcessor>());
}
