#ifndef ECPRI_PROCESSOR_H
#define ECPRI_PROCESSOR_H

#include "base/PacketProcessor.h"
#include <cstddef>
#include <memory>
#include <netinet/ip.h>

class ECPRIProcessor : public PacketProcessor {
public:
  void process(const u_int8_t *packet, size_t length,
               std::shared_ptr<PacketContext> context) override;
  void process_iq_data(const u_int8_t *packet, size_t length,
                       std::shared_ptr<PacketContext> context);
  void process_bit_seq(const u_int8_t *packet, size_t length,
                       std::shared_ptr<PacketContext> context);

  std::string get_name() const override { return "eCPRI"; }

  // Register all IP protocol handlers
  void register_handlers() override;
};

#endif // !ECPRI_PROCESSOR_H
