#include "link/EthernetProcessor.h"
#include "EcpriProtocols.h"
#include "Protocols.h"
#include "base/ProtocolRegistry.h"
#include "network/ARPProcessor.h"
#include "network/EcpriProcessor.h"
#include "network/IPProcessor.h"
#include "network/IPV6Processor.h"
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
    std::cout << "Protocol: Ethernet\n";
    print_header(ethernet);
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
              << "\n\n";
  }
}

void EthernetProcessor::register_handlers() {
  auto &registry = ProtocolRegistry::get_instance();
  registry.register_network(ETHERTYPE_IP, std::make_shared<IPProcessor>());
  registry.register_network(ETHERTYPE_ECPRI,
                            std::make_shared<ECPRIProcessor>());
  registry.register_network(ETHERTYPE_ARP, std::make_shared<ARPProcessor>());
  registry.register_network(ETHERTYPE_IPV6, std::make_shared<IPV6Processor>());
}

void EthernetProcessor::print_header(const struct eth_hdr *eth_header) {
  // Print destination MAC address
  std::cout << "Destination MAC: ";
  for (int i = 0; i < ETHER_ADDR_LEN; i++) {
    std::cout << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(eth_header->ether_dhost[i]);
    if (i < ETHER_ADDR_LEN - 1)
      std::cout << ":";
  }
  std::cout << std::endl;

  // Print source MAC address
  std::cout << "Source MAC: ";
  for (int i = 0; i < ETHER_ADDR_LEN; i++) {
    std::cout << std::hex << std::setw(2) << std::setfill('0')
              << static_cast<int>(eth_header->ether_shost[i]);
    if (i < ETHER_ADDR_LEN - 1)
      std::cout << ":";
  }
  std::cout << std::endl;

  // Print EtherType (in hex)
  std::cout << "EtherType: 0x" << std::hex << std::setw(4) << std::setfill('0')
            << ntohs(eth_header->ether_type) << std::endl;
  // Reset stream format
  std::cout << std::dec;

  std::cout << "\n";
}
