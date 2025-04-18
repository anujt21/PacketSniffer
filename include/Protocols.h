#ifndef PROTOCOLS_H
#define PROTOCOLS_H

#include <netinet/in.h>
#include <pcap.h>
#include <sys/types.h>

// Ethernet addresses are of 6 bytes
#define ETHER_ADDR_LEN 6

// Ethernet header size
#define SIZE_ETHERNET 14

/************************************************************************************
 * Link layer
 ************************************************************************************/

// Ethernet header
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

// ECPRI header
#define ETHERTYPE_ECPRI 0xAEFE

struct ecpri_hdr {
  u_char ecpri_prc;
  u_char ecpri_msg_type;
  u_short ecpri_size;
};
#define ECPRI_REV(ecpri) (((ecpri)->ecpri_prc) >> 4)
#define ECPRI_C(ecpri) (((ecpri)->ecpri_prc) & 0x01)

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
