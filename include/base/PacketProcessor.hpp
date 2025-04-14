#ifndef PACKET_PROCESSOR_H
#define PACKET_PROCESSOR_H

#include <cstdint>
#include <memory>
#include <pcap.h>
#include <string>
#include <sys/types.h>

class PacketProcessor {
public:
  virtual ~PacketProcessor() = default;

  virtual void process(const u_int8_t *packet, size_t length) = 0;

  virtual std::string getName() const = 0;
};

// Packet handler function
void packet_handler

#endif
