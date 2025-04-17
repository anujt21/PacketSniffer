#include "base/ProtocolRegistry.h"
#include <iostream>
#include <memory>
#include <sys/types.h>

void ProtocolRegistry::register_link(
    int link_type, std::shared_ptr<PacketProcessor> processor) {
  network_processors[link_type] = processor;
}
void ProtocolRegistry::register_network(
    u_int16_t network_type, std::shared_ptr<PacketProcessor> processor) {
  network_processors[network_type] = processor;
}

void ProtocolRegistry::register_transport(
    u_int8_t transport_type, std::shared_ptr<PacketProcessor> processor) {
  transport_processors[transport_type] = processor;
}

std::shared_ptr<PacketProcessor>
ProtocolRegistry::get_link_processor(int link_type) {
  auto it = link_processors.find(link_type);
  if (it != link_processors.end()) {
    return it->second;
  }
  return nullptr;
}

std::shared_ptr<PacketProcessor>
ProtocolRegistry::get_network_processor(u_int16_t network_type) {
  auto it = network_processors.find(network_type);
  if (it != network_processors.end()) {
    return it->second;
  }
  return nullptr;
}

std::shared_ptr<PacketProcessor>
ProtocolRegistry::get_transport_processor(u_int8_t transport_type) {
  auto it = transport_processors.find(transport_type);
  if (it != transport_processors.end()) {
    return it->second;
  }
  return nullptr;
}

void ProtocolRegistry::list_registered_handlers() const {
  // Registered link processors
  std::cout << "Registered link handlers: \n";
  for (const auto &[link_type, processor] : link_processors) {
    if (processor) {
      std::cout << "Link type: " << link_type;
      std::cout << ", processor name: " << processor->get_name() << std::endl;
    } else {
      std::cout << "Ethernet type: " << link_type;
      std::cout << ", processor name: Not found" << std::endl;
    }
  }
  // Registered network processors
  std::cout << "Registered network handlers: \n";
  for (const auto &[network_type, processor] : network_processors) {
    if (processor) {
      std::cout << "Network type: " << network_type;
      std::cout << ", processor name: " << processor->get_name() << std::endl;
    } else {
      std::cout << "Network type: " << network_type;
      std::cout << ", processor name: Not found" << std::endl;
    }
  }

  // Registered transport processors
  std::cout << "Registered tansport handlers: \n";
  for (const auto &[transport_type, processor] : transport_processors) {
    if (processor) {
      std::cout << "Protocl type: " << transport_type;
      std::cout << ", processor name: " << processor->get_name() << std::endl;
    } else {
      std::cout << "Protocl type: " << transport_type;
      std::cout << ", processor name: Not found" << std::endl;
    }
  }
}
