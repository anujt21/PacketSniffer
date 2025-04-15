#include "base/ProtocolRegistry.hpp"
#include <iostream>
#include <memory>
#include <sys/types.h>

void ProtocolRegistry::registerEtherType(
    u_int16_t etherType, std::shared_ptr<PacketProcessor> processor) {
  etherTypeProcessors[etherType] = processor;
}

void ProtocolRegistry::registerIPProtocol(
    u_int8_t protocol, std::shared_ptr<PacketProcessor> processor) {
  ipProtocolProcessors[protocol] = processor;
}

std::shared_ptr<PacketProcessor>
ProtocolRegistry::getEtherTypeProcessor(u_int16_t etherType) {
  auto it = etherTypeProcessors.find(etherType);
  if (it != etherTypeProcessors.end()) {
    return it->second;
  }
  return nullptr;
}

std::shared_ptr<PacketProcessor>
ProtocolRegistry::getipProtocolProcessors(u_int8_t protocol) {
  auto it = ipProtocolProcessors.find(protocol);
  if (it != ipProtocolProcessors.end()) {
    return it->second;
  }
  return nullptr;
}

void ProtocolRegistry::listRegisteredProcessors() const {
  // Registered ethernet processors
  std::cout << "Registered ethernet handlers: \n";
  for (const auto &[etherType, processor] : etherTypeProcessors) {
    if (processor) {
      std::cout << "Ethernet type: " << etherType;
      std::cout << ", processor name: " << processor->getName() << std::endl;
    } else {
      std::cout << "Ethernet type: " << etherType;
      std::cout << ", processor name: Not found" << std::endl;
    }
  }

  // Registered ip protocol processors
  std::cout << "Registered ip protocol handlers: \n";
  for (const auto &[protocol, processor] : ipProtocolProcessors) {
    if (processor) {
      std::cout << "Protocl type: " << protocol;
      std::cout << ", processor name: " << processor->getName() << std::endl;
    } else {
      std::cout << "Protocl type: " << protocol;
      std::cout << ", processor name: " << processor->getName() << std::endl;
    }
  }
}
