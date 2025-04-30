#include "session/TLSProcessor.h"
#include "Protocols.h"
#include "base/ProtocolRegistry.h"
#include "utils/HelperFunctions.h"
#include "utils/PrintData.h"

void TLSProcessor::process(const u_int8_t *packet, size_t length,
                           std::shared_ptr<PacketContext> context) {
  if (length < MIN_TLS_SIZE) {
    std::cerr << "Packet too short for TLS header";
    return;
  }

  const struct tls_hdr *tls = (struct tls_hdr *)(packet);
  u_short payload_size = ntohs(tls->length);

  if (context->verbose) {
    std::cout << "Protocol: " << get_tls_version(ntohs(tls->protocol_version))
              << "\n";
    std::cout << "Content type: " << (int)tls->content_type << "\n";
    std::cout << "Payload length " << payload_size << "\n";
  }

  u_char *payload = (u_char *)(packet + 5);

  if (payload_size > 0) {
    std::cout << "Payload (" << payload_size << " bytes): \n";
    print_payload(payload, payload_size);
  }
}

void TLSProcessor::register_handlers() { return; }
