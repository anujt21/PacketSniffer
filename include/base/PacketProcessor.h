#ifndef PACKET_PROCESSOR_H
#define PACKET_PROCESSOR_H

#include <cstdint>
#include <iostream>
#include <memory>
#include <pcap.h>
#include <pcap/dlt.h>
#include <pcap/pcap.h>
#include <string>
#include <sys/types.h>

class PacketContext {
public:
  bool verbose = false;
  u_int64_t packet_count = 0;
  int link_type = DLT_EN10MB;
};

class PacketProcessor {
public:
  virtual ~PacketProcessor() = default;

  virtual void process(const u_int8_t *packet, size_t length,
                       std::shared_ptr<PacketContext> context) = 0;

  virtual std::string get_name() const = 0;

  virtual void register_handlers() {};
};

// Packet handler function
void packet_handler(u_char *user_data, const struct pcap_pkthdr *pkthdr,
                    const u_char *packet);

#endif
