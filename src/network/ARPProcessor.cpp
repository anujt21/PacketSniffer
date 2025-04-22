#include "network/ARPProcessor.h"
#include "Protocols.h"
#include "base/PacketProcessor.h"
#include "base/ProtocolRegistry.h"
#include "link/EthernetProcessor.h"
#include "utils/PrintData.h"
#include <arpa/inet.h>
#include <cstddef>
#include <memory>
#include <netinet/in.h>
#include <sys/types.h>

void ARPProcessor::process(const u_int8_t *packet, size_t length,
                           std::shared_ptr<PacketContext> context) {
  if (length < sizeof(struct arp_hdr)) {
    std::cerr << "Packet length " << length
              << " bytes too short for ARP protocol" << sizeof(arp_hdr) << "\n";
    std::cerr << "\n";
    return;
  }

  const struct arp_hdr *arp = (struct arp_hdr *)(packet);

  // int src_haddr = ARP_SRC_HADDR(arp);
  // int dest_haddr = ARP_DEST_HADDR(arp);
  std::cout << arp->arp_opcode;

  if (context->verbose) {
    // packet info
    std::cout << "Protocol: ARP\n";
    std::cout << "Hardware type: " << arp->arp_htype << "\n";
    std::cout << "Protocol type: " << arp->arp_ptype << "\n";
    std::cout << "Sender mac address: " << print_mac(arp->src_mac) << "\n";
    std::cout << "Sender ip address: " << print_ip(arp->arp_src_paddr) << "\n";
    std::cout << "Target mac address: " << print_mac(arp->dest_mac) << "\n";
    std::cout << "Target ip address: " << print_ip(arp->arp_dest_paddr) << "\n";
  }

  if (ntohs(arp->arp_opcode) == 1) {
    std::cout << "Who has " << print_ip(arp->arp_dest_paddr) << "? Tell "
              << print_ip(arp->arp_src_paddr) << "\n";
    std::cout << "\n";
    return;
  } else if (ntohs(arp->arp_opcode) == 2) {
    std::cout << print_ip(arp->arp_src_paddr) << " is at "
              << print_mac(arp->src_mac) << "\n";
    std::cout << "\n";
    return;
  }
}
