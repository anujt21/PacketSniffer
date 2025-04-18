#include "network/IPProcessor.h"
#include "Protocols.h"
#include "base/PacketProcessor.h"
#include "base/ProtocolRegistry.h"
#include "link/EthernetProcessor.h"
#include "transport/TCPProcessor.h"
#include <arpa/inet.h>
#include <cstddef>
#include <memory>
#include <netinet/in.h>
#include <sys/types.h>

void IPProcessor::process(const u_int8_t *packet, size_t length,
                          std::shared_ptr<PacketContext> context) {
  if (length < sizeof(struct ip_hdr)) {
    std::cerr << "Packet too short for IP header." << std::endl;
    return;
  }
  const struct ip_hdr *ip = (struct ip_hdr *)(packet);
  int ip_size = IP_HL(ip) * 4;

  // TODO: Remove dependency on context
  context->ip_size = ip_size;
  context->ip_payload_len = ntohs(ip->ip_len);
  if (ip_size < 20) {
    std::cerr << "Invalid IP header length: " << ip_size << " bytes"
              << std::endl;
    return;
  }

  if (context->verbose) {
    std::cout << "Protocol: IP\n";
    std::cout << "From:       " << inet_ntoa(ip->ip_src) << "\n";
    std::cout << "To:         " << inet_ntoa(ip->ip_dst) << "\n";
  }

  const u_int8_t *payload = packet + ip_size;
  size_t payload_length = length - ip_size;

  auto &registry = ProtocolRegistry::get_instance();
  auto transport_processor = registry.get_transport_processor(ip->ip_p);

  if (transport_processor) {
    transport_processor->process(payload, payload_length, context);
  } else {
    std::cerr << "Transport processor not found for tranpsort type "
              << static_cast<int>(ip->ip_p) << "\n";
    std::cerr << "\n";
    return;
  }
}

void IPProcessor::register_handlers() {
  auto &registry = ProtocolRegistry::get_instance();
  registry.register_transport(IPPROTO_TCP, std::make_shared<TCPProcessor>());
}
