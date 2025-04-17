#include "transport/TCPProcessor.h"
#include "Protocols.h"
#include "base/PacketProcessor.h"
#include "base/ProtocolRegistry.h"
#include "utils/PrintData.h"
#include <memory>
#include <sys/types.h>

void TCPProcessor::process(const u_int8_t *packet, size_t length,
                           std::shared_ptr<PacketContext> context) {

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
  }

  u_char *payload = (u_char *)(packet + tcp_size);
  int payload_size = context->ip_payload_len - context->ip_size - tcp_size;

  if (payload_size > 0) {
    std::cout << "Payload (" << payload_size << " bytes): \n";
    print_payload(payload, payload_size);
  }
}

void TCPProcessor::register_handlers() { return; }
