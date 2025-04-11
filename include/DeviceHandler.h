#include <pcap.h>
#include <pcap/pcap.h>

class DeviceHandler {

private:
  pcap_t *handle;
  pcap_if_t *device;
  char *device_name;
  bpf_u_int32 net;
  bpf_u_int32 mask;

public:
  char errbuf[PCAP_ERRBUF_SIZE];

  DeviceHandler() = default;
  ~DeviceHandler();

  int open_live_device();
  int open_pcap_file(const char *filename);

  pcap_t *get_handler();
  char *get_device_name();
  bpf_u_int32 get_net();
  bpf_u_int32 get_mask();
};
