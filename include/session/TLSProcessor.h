#ifndef TLS_PROCESSOR_H
#define TLS_PROCESSOR_H

#include "base/PacketProcessor.h"
#include <cstddef>
#include <memory>
#include <sys/types.h>

class TLSProcessor : public PacketProcessor {
public:
  void process(const u_int8_t *packet, size_t length,
               std::shared_ptr<PacketContext> context) override;

  std::string get_name() const override { return "TLS"; }

  void register_handlers() override;
};

#endif // !TLS_PROCESSOR_H!
