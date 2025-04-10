#ifndef PACKET_HANDLER_H
#define PACKET_HANDLER_H

#include <pcap.h>
#include <pcap/pcap.h>
#include <stdio.h>
#include <sys/types.h>

void handle_packet(u_char *args, const struct pcap_pkthdr *header,
                   const u_char *packet);

void print_payload(const u_char *payload, int len);

void print_hex_asdcii_line(const u_char *payload, int len, int offset);

void print_app_banner(void);

void print_app_usage(void);

#endif // !PACKET_HANDLER_H
