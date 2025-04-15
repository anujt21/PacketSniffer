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
  void registerEtherType(u_int16_t etherType,
                         std::shared_ptr<PacketProcessor> processor);

  void registerIPProtocol(u_int8_t protocol,
                          std::shared_ptr<PacketProcessor> processor);

  // Get processors for specific protocols
  std::shared_ptr<PacketProcessor> getEtherTypeProcessor(u_int16_t etherType);
  std::shared_ptr<PacketProcessor> getipProtocolProcessors(u_int8_t protocol);

  // Display all registered processors (for debugging)
  void listRegisteredProcessors() const;

private:
  // Private constructor and destructor (accessed by Singleton)
  ProtocolRegistry() = default;
  ~ProtocolRegistry() = default;

  // Maps to store protocol processors
  std::map<u_int16_t, std::shared_ptr<PacketProcessor>> etherTypeProcessors;
  std::map<u_int8_t, std::shared_ptr<PacketProcessor>> ipProtocolProcessors;
};

#endif
