// Author: Anuj T.
// This program sniff packets from an ethernet device and prints
// the information about it.
// TODO: Remove the ethernet check and make the program protocol agnostic

#include "DeviceHandler.h"
#include "PacketHandler.h"
#include <iostream>
#include <memory>
#include <optional>
#include <pcap.h>
#include <pcap/pcap.h>
#include <string>
#include <sys/types.h>

int main(int argc, char *argv[]) {

  // Initialize variables
  std::optional<std::string> pcap_file;
  std::string pcap_file_filename;
  std::string filter = "";
  int num_packets = 0;
  bool live_mode = true;
  u_char *user_data = nullptr;

  for (int i = 0; i < argc; i++) {

    std::string arg = argv[i];

    if (arg == "-h" || arg == "--help") {
      std::cout << "Packet sniffer [OPTIONS]\n";
      std::cout << "  -f, --file=FILENAME       Read packets from PCAP file.\n";
      std::cout << "  -F, --filter=STRING       Apply filter to captured "
                   "packets.\n";
      std::cout << "  -n, --num_packets=NUMBER  Number of packets to read "
                   "(default 0).\n";
      std::cout << "  -h, --help                Display this help message.\n";

      return 0;
    } else if (arg == "-f" && i + 1 < argc) {
      pcap_file = argv[++i];
    } else if (arg.substr(0, 7) == "--file=") {
      pcap_file = arg.substr(7);
    } else if (arg == "-F" && i + 1 < argc) {
      filter = argv[++i];
    } else if (arg.substr(0, 9) == "--filter=") {
      filter = arg.substr(9);
    } else if (arg == "-n" && i + 1 < argc) {
      num_packets = std::stoi(argv[++i]);
    } else if (arg.substr(0, 14) == "--num_packets") {
      num_packets = std::stoi(arg.substr(14));
    }
  }

  // Print usage info
  print_app_usage();

  // Set capture mode
  if (pcap_file.has_value()) {
    std::cout << "Reading " << num_packets
              << "packets from file: " << *pcap_file << std::endl;
    live_mode = false;
    pcap_file_filename = pcap_file.value();
  } else {
    std::cout << "Using live capture to read " << num_packets << std::endl;
  }

  std::unique_ptr<DeviceHandler> device_handler =
      std::make_unique<DeviceHandler>();

  if (filter.length() > 0) {
    device_handler->set_filter_exp(filter);
  }

  if (live_mode) {
    if (device_handler->open_live_device() == -1) {
      return 1;
    };
  } else {
    if (device_handler->open_pcap_file(
            const_cast<char *>(pcap_file_filename.c_str())) == -1) {
      return 1;
    };
  }

  // Caputre packets
  if (device_handler->capture_packets(num_packets, user_data) == -1) {
    return 1;
  }

  return (0);
}
