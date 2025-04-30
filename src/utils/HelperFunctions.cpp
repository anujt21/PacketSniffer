#include "utils/HelperFunctions.h"
#include "Protocols.h"

std::string get_tls_version(int value) {
  switch (value) {
  case SSL_3_0:
    return "SSL3.0";
  case TLS_1_0:
    return "TLS1.0";
  case TLS_1_1:
    return "TLS1.1";
  case TLS_1_2:
    return "TLS1.2";
  case TLS_1_3:
    return "TLS1.3";
  default:
    return "(unknown version)";
  }
}

bool isTLS(int version) {
  switch (version) {
  case SSL_3_0:
  case TLS_1_0:
  case TLS_1_1:
  case TLS_1_2:
  case TLS_1_3:
    return true;
  default:
    return false;
  }
}
