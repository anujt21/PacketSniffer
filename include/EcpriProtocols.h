#ifndef ECPRI_PROTOCOLS_H
#define ECPRI_PROTOCOLS_H

#include <netinet/in.h>
#include <pcap.h>
#include <sys/types.h>

#define ETHERTYPE_ECPRI 0xAEFE

struct ecpri_hdr {
  u_char ecpri_prc;
  u_char ecpri_msg_type;
  u_short ecpri_size;
};
#define ECPRI_REV(ecpri) (((ecpri)->ecpri_prc) >> 4)
#define ECPRI_C(ecpri) (((ecpri)->ecpri_prc) & 0x01)

struct ecpri_iq_data {
  u_short pc_id;
  u_short seq_id;
  u_char *iq_data;
};

struct ecpri_bit_seq {
  u_short pc_id;
  u_short seq_id;
  u_char *bit_seq;
};

#endif //! ECPRI_PROTOCOLS_H
