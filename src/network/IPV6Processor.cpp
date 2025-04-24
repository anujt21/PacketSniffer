#include "network/IPV6Processor.h"
#include "Protocols.h"
#include "base/PacketProcessor.h"
#include "base/ProtocolRegistry.h"
#include "link/EthernetProcessor.h"
#include "transport/TCPProcessor.h"
#include "utils/PrintData.h"
#include <arpa/inet.h>
#include <cstddef>
#include <memory>
#include <netinet/in.h>
#include <sys/types.h>

void IPV6Processor::process(const u_int8_t *packet, size_t length,
                            std::shared_ptr<PacketContext> context) {
  if (length < SIZE_IPV6) {
    std::cerr << "Packet " << length << " bytes too short for IPV6 header.\n";
    return;
  }

  const struct ipv6_hdr *ipv6 = (struct ipv6_hdr *)(packet);
  int ipv6_traffic_class = IPV6_TC(ipv6);
  int ipv6_flow_label = IPV6_FL(ipv6);
  print_ipv6(ipv6->ipv6_dest_addr);

  if (context->verbose) {
    std::cout << "Protocol: IPV6";
    std::cout << "IPV6 soruce address: " << print_ipv6(ipv6->ipv6_src_addr)
              << "\n";
    std::cout << "IPV6 destination address: "
              << print_ipv6(ipv6->ipv6_dest_addr) << "\n";
    std::cout << "\n";
  }

  const u_int8_t *payload = packet + SIZE_IPV6;
  size_t payload_length = length - SIZE_IPV6;

  auto &registry = ProtocolRegistry::get_instance();
  auto transport_processor =
      registry.get_transport_processor(ipv6->ipv6_next_hdr);

  if (transport_processor) {
    transport_processor->process(payload, payload_length, context);
  } else {
    std::cerr << "Trasnsport processor not found for transport type "
              << static_cast<int>(ipv6->ipv6_next_hdr) << "\n";
    std::cerr << "\n";
    return;
  }
}

void IPV6Processor::register_handlers() {
  // TODO: Add protocols related to ipv6 here.
  return;
}
