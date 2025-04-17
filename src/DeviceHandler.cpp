#include "DeviceHandler.h"
#include "base/PacketProcessor.h"
#include <cstdio>
#include <iostream>
#include <ostream>
#include <pcap/dlt.h>
#include <pcap/pcap.h>
#include <sys/types.h>

int DeviceHandler::open_live_device() {

  pcap_if_t *alldevs = nullptr;

  // Find available devices
  if (pcap_findalldevs(&alldevs, errbuf) == -1) {
    std::cerr << "Error finding devices: " << errbuf << std::endl;
    return -1;
  }

  if (alldevs == nullptr) {
    std::cerr << "No devices found." << std::endl;
    return -1;
  }

  // Set device name
  device = alldevs;
  device_name = device->name;

  // Loop up device's network mask and open a session
  if (pcap_lookupnet(const_cast<char *>(device_name.c_str()), &net, &mask,
                     errbuf) == -1) {
    std::cerr << "Cannot get netmasks for device " << device_name << std::endl;
    return -1;
  }

  handle = pcap_open_live(const_cast<char *>(device_name.c_str()), BUFSIZ, 1,
                          1000, errbuf);
  if (handle == nullptr) {
    std::cerr << "Could not open device " << device_name << std::endl;
    return -1;
  }

  if (!ethernet_handle_check(handle)) {
    std::cerr << "Device " << device_name << "does not provide ethernet headers"
              << std::endl;
    return -1;
  }
  // Compile and set the BPF filter
  if (filter_exp.length() > 0) {
    if (pcap_compile(handle, &fp, const_cast<char *>(filter_exp.c_str()), 0,
                     net) == -1) {
      std::cerr << "Could not parse filter " << filter_exp << ": "
                << pcap_geterr(handle);
      return -1;
    }

    if (pcap_setfilter(handle, &fp) == -1) {
      std::cerr << "Could not set filer " << filter_exp << ": "
                << pcap_geterr(handle);
      return -1;
    }
  }

  return 0;
}

int DeviceHandler::open_pcap_file(const char *filename) {

  handle = pcap_open_offline(filename, errbuf);

  if (handle == nullptr) {
    std::cerr << "Could not open pcap file " << filename << ": " << errbuf
              << std::endl;
    return -1;
  }

  std::cout << "Opened pcap file: " << filename << std::endl;
  return 0;
}

// Capture packets using pcap_loop
int DeviceHandler::capture_packets(int num_packets, u_char *user_data) {
  if (handle == nullptr) {
    std::cerr << "Handle is a null pointer." << std::endl;
    return -1;
  }
  if (pcap_loop(handle, num_packets, packet_handler, user_data) == -1) {
    std::cerr << "Error in capturing packets: " << errbuf;
    return -1;
  };
  return 0;
}
