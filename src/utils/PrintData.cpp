#include "utils/PrintData.h"
#include <cctype>
#include <iomanip>
#include <iostream>
#include <string>

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
    printf("%*s", gap * 3, "");
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

std::string print_ip(u_int32_t ip) {
  // Extract each byte and print in dotted decimal format
  std::stringstream ss;
  ss << ((ip >> 24) & 0xFF) << "." << ((ip >> 16) & 0xFF) << "."
     << ((ip >> 8) & 0xFF) << "." << (ip & 0xFF);

  return ss.str();
}

std::string print_mac(uint64_t mac) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  ss << std::setw(2) << ((mac >> 40) & 0xFF) << ":" << std::setw(2)
     << ((mac >> 32) & 0xFF) << ":" << std::setw(2) << ((mac >> 24) & 0xFF)
     << ":" << std::setw(2) << ((mac >> 16) & 0xFF) << ":" << std::setw(2)
     << ((mac >> 8) & 0xFF) << ":" << std::setw(2) << (mac & 0xFF);
  ss << std::dec; // Reset to decimal output

  return ss.str();
}

std::string print_mac(const u_char mac[6]) {
  std::stringstream ss;
  ss << std::hex << std::setfill('0');
  for (int i = 0; i < 6; i++) {
    ss << std::setw(2) << static_cast<int>(mac[i]);
    if (i < 5)
      ss << ":";
  }
  return ss.str();
}
