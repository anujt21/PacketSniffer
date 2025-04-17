#include "utils/PrintData.h"
#include <cctype>

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
  int offset = 0;

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
