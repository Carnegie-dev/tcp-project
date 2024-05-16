#include <iostream>

#include "network_utils.h"

int main() {
  char *ptr = new char[20];
  auto str = network_convert_ip_n_to_p(132973457, ptr);
  printf("%s\n", str);

  auto numeric = network_convert_ip_p_to_n(str);
  printf("%d\n", numeric);
}
