#include "PacketHandler.h"
#include "Protocols.h"
#include <arpa/inet.h>
#include <ctype.h>
#include <netinet/in.h>
#include <stdio.h>
#include <sys/types.h>

void print_app_usage() {
  printf("%s - %s\n", APP_NAME, APP_DESC);
  return;
}

void print_hex_ascii_line(const u_char *payload, int len, int offset) {

  int i, gap;
  const u_char *ch = payload;

  // offset
  printf("%05d  ", offset);

  // hex
  for (i = 0; i < len; i++) {
    printf("%02x ", *ch);
    ch++;

    if (i == 7)
      printf(" ");
  }

  if (len < 8)
    printf(" ");

  if (len < 16) {
    gap = 16 - len;
    printf("%*s", gap * 3, "");
  }

  printf("  ");

  // ascii
  ch = payload;
  for (i = 0; i < len; i++) {
    if (isprint(*ch)) {
      printf("%c", *ch);
    } else {
      printf(".");
    }
    ch++;
  }

  printf("\n");

  return;
}

// print packet payload data
void print_payload(const u_char *payload, int len) {
  int len_rem = len;
  int line_width = 16;
  int line_len;
  int offset = 0;
  const u_char *ch = payload;

  if (len <= 0)
    return;

  if (len <= line_width) {
    print_hex_ascii_line(payload, len, offset);
    return;
  }

  for (;;) {
    print_hex_ascii_line(payload + offset, line_width, offset);

    len_rem = len_rem - line_width;
    offset = offset + line_width;

    if (len_rem <= 0)
      break;

    if (len_rem <= line_width) {
      print_hex_ascii_line(payload + offset, len_rem, offset);
      break;
    }
  }
}

void handle_packet(u_char *args, const struct pcap_pkthdr *header,
                   const u_char *packet) {

  static int packet_counter = 1;
  int size_ip, size_tcp, size_payload;

  // declare pointers to packet headers
  const struct sniff_ethernet *ethernet;
  const struct sniff_ip *ip;
  const struct sniff_tcp *tcp;
  const u_char *payload;

  printf("\nPacket number %d:\n", packet_counter);
  packet_counter++;

  ethernet = (struct sniff_ethernet *)(packet);
  ip = (struct sniff_ip *)(packet + SIZE_ETHERNET);
  size_ip = IP_HL(ip) * 4;
  if (size_ip < 20) {
    printf("Invalid IP header length: %u bytes\n", size_ip);
    return;
  }

  printf("From: %s\n", inet_ntoa(ip->ip_src));
  printf("To: %s\n", inet_ntoa(ip->ip_dst));

  // determine protocol
  switch (ip->ip_p) {
  case IPPROTO_TCP:
    printf("  protocol: TCP\n");
    break;
  case IPPROTO_UDP:
    printf("  protocol: UDP\n");
    return;
  case IPPROTO_ICMP:
    printf("  protocol: ICMP\n");
    return;
  case IPPROTO_IP:
    printf("  protocol: IP\n");
    return;
  default:
    printf("  protocol: unknown %d\n", ip->ip_p);
    return;
  }

  // determine tcp header obreakffset
  tcp = (struct sniff_tcp *)(packet + SIZE_ETHERNET + size_ip);
  size_tcp = TH_OFF(tcp) * 4;
  if (size_tcp < 20) {
    printf("Invalid TCP header length: %u bytes\n", size_tcp);
    return;
  }

  // print port numbers
  printf("Source port:      %d\n", ntohs(tcp->th_sport));
  printf("Desitnation port: %d\n", ntohs(tcp->th_dport));

  payload = (u_char *)(packet + SIZE_ETHERNET + size_tcp + size_ip);
  size_payload = (ip->ip_len) - (size_ip + size_tcp);

  if (size_payload > 0) {
    printf("  Payload (%d bytes):\n", size_payload);
    print_payload(payload, size_payload);
  }

  return;
}
