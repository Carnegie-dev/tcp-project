#include <cstring>
#include <sstream>

#include "network_utils.h"

char *network_convert_ip_n_to_p(uint32_t ip_addr, char *output_buffer) {
  uint8_t tmp[4] = {0, 0, 0, 0};
  int idx = 0;
  while (ip_addr > 0) {
    tmp[idx++] = ip_addr & 0xff;
    ip_addr >>= 8;
  }

  char *output = output_buffer;
  if (!output) {
    static char static_buffer[16] = {0};
    output = static_buffer;
  }
  memset(output, 0, 16 * sizeof(char));
  sprintf(output, "%d.%d.%d.%d", tmp[3], tmp[2], tmp[1], tmp[0]);

  return output;
}

uint32_t network_convert_ip_p_to_n(const char *ip_addr) {
  uint32_t numeric = 0;

  std::istringstream stream(ip_addr);
  for (std::string byte; getline(stream, byte, '.');) {
    numeric <<= 8;
    numeric |= std::stoi(byte);
  }
  return numeric;
}
