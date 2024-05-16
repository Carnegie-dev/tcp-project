#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstdlib>

bool connect_to_server(const char *ip_addr, const char *port_no) {
  // Socket creation
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("Error opening socket");
    exit(EXIT_FAILURE);
  }

  int optval = 1;
  /* if (setsockopt(
      sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) < 0) {
    perror("Error setting socket option SO_REUSEADDR");
  }
  if (setsockopt(
      sockfd, SOL_SOCKET, SO_REUSEPORT, &optval, sizeof(optval)) < 0) {
    perror("Error setting socket option SO_REUSEADDR");
  } */

  // Prepare the server address structure
  struct sockaddr_in serv_addr;
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(std::stoul(port_no));  // Server's port number
  inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr); // Server's IP address

  std::cout << "Connecting to " << ip_addr << ":" << port_no << std::endl;
  // Connecting to the server
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }

  return true;
}

int main(int argc, char** argv) {
  if (argc != 3) {
    std::cerr << "Incorrect arguments.";
    exit(0);
  }

  connect_to_server(argv[1], argv[2]);
}