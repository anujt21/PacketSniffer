#include <pcap.h>
#include <pcap/pcap.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <sys/types.h>

#define APP_NAME "PacketSniffer"
#define APP_DESC "Sniff packets using libpcap"

void print_payload(const u_char *payload, int len);

void print_hex_ascii_line(const u_char *payload, int len, int offset);

void print_app_usage();

std::string print_ip(u_int32_t ip);

std::string print_mac(uint64_t mac);

std::string print_mac(const u_char mac[6]);
