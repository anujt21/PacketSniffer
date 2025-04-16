#ifndef PROTOCOL_REGISTRY_H
#define PROTOCOL_REGISTRY_H

#include "PacketProcessor.hpp"
#include "utils/Singleton.hpp"
#include <cstdint>
#include <map>
#include <memory>
#include <sys/types.h>

class ProtocolRegistry : public Singleton<ProtocolRegistry> {

  // Allow Singleton to access private constructor/destructor
  friend class Singleton<ProtocolRegistry>;

public:
  // Register protocol processors
  void register_link(int link_type, std::shared_ptr<PacketProcessor> processor);
  void register_network(u_int16_t network_type,
                        std::shared_ptr<PacketProcessor> processor);
  void register_transport(u_int8_t transport_type,
                          std::shared_ptr<PacketProcessor> processor);

  // Get processors for specific protocols
  std::shared_ptr<PacketProcessor> get_link_processor(int link_type);
  std::shared_ptr<PacketProcessor>
  get_network_processor(u_int16_t network_type);
  std::shared_ptr<PacketProcessor>
  get_transport_processor(u_int8_t transport_type);

  // Display all registered processors (for debugging)
  void list_registered_handlers() const;

private:
  // Private constructor and destructor (accessed by Singleton)
  ProtocolRegistry() = default;
  ~ProtocolRegistry() = default;

  // Maps to store processors
  std::map<int, std::shared_ptr<PacketProcessor>> link_processors;
  std::map<u_int16_t, std::shared_ptr<PacketProcessor>> network_processors;
  std::map<u_int8_t, std::shared_ptr<PacketProcessor>> transport_processors;
};

#endif
