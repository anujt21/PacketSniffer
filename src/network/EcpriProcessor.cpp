#include "network/EcpriProcessor.h"
#include "Protocols.h"
#include "utils/PrintData.h"
#include <cstddef>
#include <memory>
#include <netinet/ip.h>
#include <sys/types.h>

void ECPRIProcessor::process(const u_int8_t *packet, size_t length,
                             std::shared_ptr<PacketContext> context) {
  if (length < sizeof(struct ecpri_hdr)) {
    std::cerr << "Packet too short for ecpr i headr." << std::endl;
    return;
  }
  const struct ecpri_hdr *ecpri = (struct ecpri_hdr *)(packet);
  u_char *payload = (u_char *)(packet + 4);
  int payload_length = length - 4;

  if (context->verbose) {
    std::cout << "Protocol: eCPRI " << ECPRI_REV(ecpri) << "\n";
    std::cout << "Message type: " << ecpri->ecpri_msg_type << "\n";
    if (ECPRI_C(ecpri)) {
      std::cout << "Another eCPRI message follows.\n";
    } else {
      std::cout << "Last message inside the eCPRI PDU.\n";
    }
  }

  if (payload_length > 0) {
    std::cout << "Payload (" << payload_length << " bytes: \n";
    print_payload(payload, payload_length);
  }
}

void ECPRIProcessor::register_handlers() { return; }
