#include "DeviceHandler.h"
#include <cstddef>
#include <iostream>
#include <ostream>
#include <pcap/pcap.h>

int DeviceHandler::open_live_device() {

  pcap_if_t *alldevs;

  // Find available devices
  if (pcap_findalldevs(&alldevs, errbuf) == -1) {
    std::cerr << "Error finding devices: " << errbuf << std::endl;
    return 2;
  }

  if (alldevs == nullptr) {
    std::cerr << "No devices found." << std::endl;
    return 2;
  }

  // Set device name
  device = alldevs;
  device_name = device->name;

  // Loop up device's network mask and open a session
  if
}
