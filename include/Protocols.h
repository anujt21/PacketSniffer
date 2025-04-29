#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <netinet/in.h>
#include <pcap.h>
#include <sys/types.h>

/************************************************************************************
 * Link layer
 ************************************************************************************/

// Ethernet header
#define ETHER_ADDR_LEN 6
#define SIZE_ETHERNET 14
struct eth_hdr {
  u_char ether_dhost[ETHER_ADDR_LEN];
  u_char ether_shost[ETHER_ADDR_LEN];
  u_short ether_type;
};

/************************************************************************************
 * Network layer
 ************************************************************************************/

// IP header
struct ip_hdr {
  u_char ip_vhl;                 // version << 4 | header length >> 2
  u_char ip_tos;                 // types of service
  u_short ip_len;                // total length
  u_short ip_id;                 // identification
  u_short ip_off;                // fragment offset field
#define IP_RF 0x8000             // reserverd fragment flag
#define IP_DF 0x4000             // dont fragment flag
#define IP_MF 0x2000             // more fraagments flag
#define IP_OFFMASK 0x1fff        // mask for fragmenting bits
  u_char ip_ttl;                 // time to live
  u_char ip_p;                   // protocol
  u_short ip_sum;                // checksum
  struct in_addr ip_src, ip_dst; // source and dest address
};
#define IP_HL(ip) (((ip)->ip_vhl) & 0x0f)
#define IP_V(ip) (((ip)->ip_vhl) >> 4)

// IPV6 header
#define SIZE_IPV6 40
struct ipv6_hdr {
  u_int32_t ipv6_v_tc_fl;
  u_short ipv6_payload_len;
  u_char ipv6_next_hdr;
  u_char ipv6_hoplimit;
  u_short ipv6_src_addr[8];
  u_short ipv6_dest_addr[8];
};
#define IPV6_V(ip) (((ip)->ipv6_v_tc_fl) & 0x0000000f)
#define IPV6_TC(ip) ((((ip)->ipv6_v_tc_fl) >> 4) & 0x00000ff)
#define IPV6_FL(ip) (((ip)->ipv6_v_tc_fl) >> 12)

// ARP header
#define SIZE_ARP 28
struct arp_hdr {
  u_short arp_htype;
  u_short arp_ptype;
  u_char arp_hlen;
  u_char arp_plen;
  u_short arp_opcode;
  u_char src_mac[6];
  // u_int32_t arp_src_haddr32;
  // u_short arp_src_haddr16;
  u_int32_t arp_src_paddr;
  u_char dest_mac[6];
  // u_int32_t arp_dest_haddr32;
  // u_short arp_dest_haddr16;
  u_int32_t arp_dest_paddr;
};
// #define ARP_SRC_HADDR(arp)                                                     \
//   ((((arp)->arp_src_haddr32) << 16) | ((arp)->arp_src_haddr16))
// #define ARP_DEST_HADDR(arp)                                                    \
//   ((((arp)->arp_dest_haddr32) << 16) | ((arp)->arp_dest_haddr16))

/************************************************************************************
 * Transport layer
 ************************************************************************************/

// TCP header
struct tcp_hdr {
  u_short th_sport; // source sport
  u_short th_dport; // dest sport
  u_int th_seq;     // sequence number
  u_int th_ack;     // acknowledgement number
  u_char th_offx2;  // data offset, rsvd
  u_char th_flags;
#define TH_FIN 0x01;
#define TH_SYN 0x02;
#define TH_RST 0x04;
#define TH_PUSH 0x08;
#define TH_ACK 0x10;
#define TH_URG 0x20;
#define TH_ECE 0x40;
#define TH_CWR 0x80;
#define TH_FLAGS (TH_FIN | TH_SYN | TH_RST | TH_URG | TH_ECE | TH_CWR | TH_ACK)
  u_short th_win; // window
  u_short th_sum; // checksum
  u_short th_urp; // urgent pointer
};
#define TH_OFF(th) (((th)->th_offx2 & 0xf0) >> 4)

#endif
