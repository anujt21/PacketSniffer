#include "utils/PrintData.h"
#include <cctype>
#include <iomanip>
#include <iostream>

void print_app_usage() {
  std::cout << APP_NAME << " - " << APP_DESC << "\n";
  std::cout << "\n";
  return;
}

void print_hex_ascii_line(const u_char *payload, int len, int offset) {

  int i, gap;
  const u_char *ch = payload;

  // offset
  printf("%05d ", offset);

  // hex
  for (i = 0; i < len; i++) {
    printf("%02x ", *ch);
    ch++;

    if (i == 7)
      std::cout << " ";
  }

  if (len < 8)
    std::cout << " ";

  if (len < 16) {
    gap = 16 - len;
    std::cout << std::setw(gap * 3) << "";
  }

  std::cout << " ";

  // ascii
  ch = payload;
  for (i = 0; i < len; i++) {
    if (isprint(*ch)) {
      std::cout << static_cast<char>(*ch);
    } else {
      std::cout << ".";
    }
    ch++;
  }

  std::cout << "\n";

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
  std::cout << "\n";
}
