#include <pcap.h>
#include <pcap/pcap.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define SNAP_LEN

int main(int argc, char *argv[]) {

  // Initialize variables
  char errbuf[PCAP_ERRBUF_SIZE];
  char filter_exp[] = "";
  pcap_if_t *alldevs;
  pcap_if_t *dev;
  pcap_t *device_handle;
  struct bpf_program fp;
  bpf_u_int32 mask;
  bpf_u_int32 net;
  struct pcap_pkthdr header;
  const u_char *packet;

  // Find the device
  if (!pcap_findalldevs(&alldevs, errbuf)) {
    printf("Successfully found devices\n");
  } else {
    fprintf(stderr, "Error finding devices: %s\n", errbuf);
    return 2;
  }

  if (alldevs == NULL) {
    fprintf(stderr, "No devices found.\n");
    return 2;
  }

  dev = alldevs;
  const char *device_name = dev->name;
  printf("Device: %s\n", device_name);

  // Look up device's network mask and open a live session
  if (pcap_lookupnet(device_name, &net, &mask, errbuf) == -1) {
    fprintf(stderr, "Cannot get netmaks for device %s\n", device_name);
    return 2;
  }

  device_handle = pcap_open_live(device_name, BUFSIZ, 1, 1000, errbuf);
  if (device_handle == NULL) {
    fprintf(stderr, "Could not open device %s: %s\n", device_name, errbuf);
    return 2;
  }

  // Check if the device provides ethernet headers
  if (pcap_datalink(device_handle) != DLT_EN10MB) {
    fprintf(stderr,
            "Device %s doesn't provide Ethernet headers - not supported\n",
            device_name);
    return (2);
  }

  // Compile and set the BPF filter
  if (strlen(filter_exp) > 0) {
    if (pcap_compile(device_handle, &fp, filter_exp, 0, net) == -1) {
      fprintf(stderr, "Could not parse filter %s: %s\n", filter_exp,
              pcap_geterr(device_handle));
      return 2;
    }

    if (pcap_setfilter(device_handle, &fp) == -1) {
      fprintf(stderr, "Could not install filter %s: %s\n", filter_exp,
              pcap_geterr(device_handle));
      return 2;
    }
  }

  // int success = pcap_loop(device_handle, 100, packet_handler, user_data);
  //
  // if (success == -1) {
  //   fprintf(stderr, "Error in pcap_loop: %s\n", errbuf);
  //   return 2;
  // } else if (success == -2) {
  //   printf("pcap_loop terminated.");
  // }

  pcap_freealldevs(alldevs);
  return (0);
}
