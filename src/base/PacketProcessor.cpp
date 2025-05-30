#include "base/PacketProcessor.h"
#include "Protocols.h"
#include "base/ProtocolRegistry.h"
#include "link/EthernetProcessor.h"
#include "network/IPProcessor.h"
#include <memory>
#include <net/ethernet.h>

void packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr,
                    const u_char *packet) {
  auto packet_context_ptr = reinterpret_cast<PacketContext *>(user_data);
  std::shared_ptr<PacketContext> context(packet_context_ptr,
                                         [](PacketContext *) {});
  context->packet_count++;
  std::cout << "***************************************************************"
               "****\n";
  std::cout << "PACKET NUMBER: " << context->packet_count << "\n";

  auto &registry = ProtocolRegistry::get_instance();
  auto link_processor = registry.get_link_processor(context->link_type);

  if (link_processor) {
    link_processor->register_handlers();
    link_processor->process(packet, pkthdr->len, context);
  } else {
    std::cerr << "Link processor not found with link type: "
              << context->link_type << std::endl;
  }
}
