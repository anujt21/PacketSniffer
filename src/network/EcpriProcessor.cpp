#include "network/EcpriProcessor.h"
#include "EcpriProtocols.h"
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
  std::cout << "Protocol: eCPRI " << ECPRI_REV(ecpri) << "\n";

  if (context->verbose) {
    std::cout << "Message type: " << ecpri->ecpri_msg_type << "\n";
    if (ECPRI_C(ecpri)) {
      std::cout << "Another eCPRI message follows.\n";
    } else {
      std::cout << "Last message inside the eCPRI PDU.\n";
    }
  }

  if (payload_length > 0) {
    switch (ecpri->ecpri_msg_type) {
    case 0:
      process_iq_data(payload, payload_length, context);
      break;
    case 1:
      process_bit_seq(payload, payload_length, context);
      break;
    case 2:
      // rt control data
      break;
    case 3:
      // generic data transfer
      break;
    case 4:
      // remote memory access
      break;
    case 5:
      // one way delay meas
      break;
    case 6:
      // remote reset
      break;
    case 7:
      // event indication
      break;
    default:
      std::cerr << "Message type " << ecpri->ecpri_msg_type
                << " could not be processed.\n";
      break;
    }
  } else {
    std::cout << "No payload found.\n";
    return;
  }
}

void ECPRIProcessor::process_iq_data(const u_int8_t *packet, size_t length,
                                     std::shared_ptr<PacketContext> context) {
  if (length < 4) {
    std::cerr << "Packet too short for ecpri iq data message.\n";
    return;
  }

  const struct ecpri_iq_data *ecpri_iq_data = (struct ecpri_iq_data *)(packet);
  std::cout << "Message type: IQ data\n";

  if (context->verbose) {
    std::cout << "PC ID: " << ecpri_iq_data->pc_id << "\n";
    std::cout << "SEQ ID " << ecpri_iq_data->seq_id << "\n";
    std::cout << "\n";
  }

  int payload_length = length - 4;
  if (payload_length > 0) {
    print_payload(ecpri_iq_data->iq_data, payload_length);
  }
}

void ECPRIProcessor::process_bit_seq(const u_int8_t *packet, size_t length,
                                     std::shared_ptr<PacketContext> context) {
  if (length < 4) {
    std::cerr << "Packet too short for ecpri bit sequence message.\n";
    return;
  }

  const struct ecpri_bit_seq *ecpri_bit_seq = (struct ecpri_bit_seq *)(packet);
  std::cout << "Message type: Bit Sequence\n";

  if (context->verbose) {
    std::cout << "PC ID: " << ecpri_bit_seq->pc_id << "\n";
    std::cout << "SEQ ID " << ecpri_bit_seq->seq_id << "\n";
    std::cout << "\n";
  }

  int payload_length = length - 4;
  if (payload_length > 0) {
    print_payload(ecpri_bit_seq->bit_seq, payload_length);
  }
}

void ECPRIProcessor::register_handlers() { return; }
