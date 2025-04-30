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

struct ecpri_rt_cdata {
  u_short rtc_id;
  u_short seq_id;
  u_char *rt_cdata;
};

struct ecpri_gen_data {
  u_int32_t pc_id;
  u_int32_t seq_id;
  u_char *data;
};

struct ecpri_mem_access {
  u_char mem_access_id;
  u_char rw_req;
  u_short element_id;
  u_char address[6];
  u_short length;
  u_char *data;
};

struct ecpri_delay_meas {
  u_char meas_id;
  u_char action_type;
  u_char seconds[6];
  u_char nanoseconds[4];
  u_char comp_value[8];
  u_char *dummy_bytes;
};

struct ecpri_remote_reset {
  u_short reset_id;
  u_char reset_code;
  u_char *payload;
};

#endif //! ECPRI_PROTOCOLS_H
