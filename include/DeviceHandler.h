#ifndef DEVICE_HANDLER_H
#define DEVICE_HANDLER_H

#include <cstdio>
#include <iostream>
#include <pcap.h>
#include <pcap/dlt.h>
#include <pcap/pcap.h>
#include <string>

class DeviceHandler {

private:
  pcap_t *handle = nullptr;
  pcap_if_t *device = nullptr;
  std::string device_name = "";
  bpf_u_int32 net = 0;
  bpf_u_int32 mask = 0;
  struct bpf_program fp = {};
  std::string filter_exp = "";

public:
  char errbuf[PCAP_ERRBUF_SIZE];

  DeviceHandler() = default;
  ~DeviceHandler() {
    pcap_freecode(&fp);
    pcap_close(handle);
  }

  int open_live_device();
  int open_pcap_file(const char *filename);
  int capture_packets(int num_packets, u_char *user_data);

  bool ethernet_handle_check(pcap_t *handle) {
    return pcap_datalink(handle) == DLT_EN10MB;
  }

  pcap_t *get_handler() { return handle; };
  std::string get_device_name() { return device_name; };
  bpf_u_int32 get_net() { return net; };
  bpf_u_int32 get_mask() { return mask; };
  std::string get_filter_exp() { return filter_exp; };

  void set_filter_exp(std::string f_expression) { filter_exp = f_expression; };
};

#endif // !DEVICE_HANDLER_H
