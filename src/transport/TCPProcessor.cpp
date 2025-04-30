#include "transport/TCPProcessor.h"
#include "Protocols.h"
#include "base/PacketProcessor.h"
#include "base/ProtocolRegistry.h"
#include "session/TLSProcessor.h"
#include "utils/HelperFunctions.h"
#include "utils/PrintData.h"
#include <memory>
#include <sys/types.h>

void TCPProcessor::process(const u_int8_t *packet, size_t length,
                           std::shared_ptr<PacketContext> context) {

  if (length < MIN_TCP_SIZE) {
    std::cerr << "Packet too short for TCP header";
    return;
  }

  struct tcp_hdr *tcp = (struct tcp_hdr *)(packet);
  int tcp_size = TH_OFF(tcp) * 4;
  if (tcp_size < 20) {
    std::cerr << "Invalid TCP header length: :" << tcp_size << " bytes."
              << std::endl;
    return;
  }

  if (context->verbose) {
    std::cout << "Protocol: TCP\n";
    std::cout << "Soruce port:        " << ntohs(tcp->th_sport) << "\n";
    std::cout << "Desitnation port:   " << ntohs(tcp->th_dport) << "\n";
    std::cout << "\n";
  }

  u_char *payload = (u_char *)(packet + tcp_size);
  int payload_size = length - tcp_size;

  if (payload_size == 0)
    return;

  auto &registry = ProtocolRegistry::get_instance();

  u_short tlscheck = (payload[1] << 8) | payload[2];
  // tlscheck = (*(packet + 1) << 8) | *(packet + 2);
  // std::cout << "TLS check: " << tlscheck << "\n";
  // std::cout << (int)(packet[1]) << "\n";
  // std::cout << packet[2] << "\n";
  // printf("Bytes extracted: %02x %02x\n", *(packet + 1), *(packet + 2));
  if (isTLS(tlscheck)) {
    auto session_processor = registry.get_session_processor(TCP_TLS);
    session_processor->register_handlers();
    session_processor->process(payload, payload_size, context);
  } else {
    std::cerr << "Processor not found for the payload after TCP\n";
    print_payload(payload, payload_size);
  }
}

void TCPProcessor::register_handlers() {
  auto &registry = ProtocolRegistry::get_instance();
  registry.register_session(TCP_TLS, std::make_shared<TLSProcessor>());
  return;
}
