#include "TcpNewConnectionAcceptor.h"

#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

#include "network_utils/network_utils.h"

TcpNewConnectionAcceptor::TcpNewConnectionAcceptor(
    const std::shared_ptr<TcpServerControllerInterface>& tcp_ctrlr)
    : tcp_ctrlr_(tcp_ctrlr) {
  this->accept_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (this->accept_fd < 0) {
    std::cout << "Error: Could not create Accept FD" << std::endl;
    exit(0);
  }

  this->accept_new_conn_thread = std::make_shared<pthread_t>();
}

void * tcp_listen_for_new_connections(void *arg) {
  TcpNewConnectionAcceptor *tcp_new_conn_acc = (TcpNewConnectionAcceptor *)arg;
  tcp_new_conn_acc->StartTcpNewConnectionAcceptorThreadInternal();

  return nullptr;
}

void TcpNewConnectionAcceptor::StartTcpNewConnectionAcceptorThread() {
  if (pthread_create(this->accept_new_conn_thread.get(), NULL,
                     tcp_listen_for_new_connections, (void *)this)) {
    std::cout << __FUNCTION__ << " Thread Creation failed, error = " << errno;
    exit(0);
  }

  std::cout << "Service Started: TcpNewConnectionAcceptorThread." << std::endl;
}

void TcpNewConnectionAcceptor::StartTcpNewConnectionAcceptorThreadInternal() {
  int opt = 1;
  struct sockaddr_in server_addr;

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(this->tcp_ctrlr()->port_no());
  server_addr.sin_addr.s_addr = htonl(this->tcp_ctrlr()->ip_addr());

  /*if (setsockopt(this->accept_fd, SOL_SOCKET, SO_REUSEPORT, (char *)&opt,
                 sizeof(opt)) < 0) {
    std::cout << "setsockopt Failed" << std::endl;
    exit(0);
  }

  if (setsockopt(this->accept_fd, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, sizeof (opt)) < 0) {
    std::cout << "setsockopt failed." << std::endl;
  }*/

  if (bind(this->accept_fd, (struct sockaddr *)&server_addr,
           sizeof(struct sockaddr)) == -1) {
    std::cout << "Error: Acceptor socket bind failed "
              << network_convert_ip_n_to_p(tcp_ctrlr()->ip_addr(), 0) << ":"
              << tcp_ctrlr()->port_no() << ", " << errno;
    exit(0);
  }

  if (listen(this->accept_fd, 5) < 0) {
    std::cout << "listen failed." << std::endl;
    exit(0);
  }

  struct sockaddr_in client_addr;
  socklen_t addr_len = sizeof(client_addr);
  int comm_sock_fd;

  while (true) {
    std::cout << "Tcp Server is listening ..." << std::endl;
    comm_sock_fd =
        accept(this->accept_fd, (struct sockaddr *)&client_addr, &addr_len);
    if (comm_sock_fd < 0) {
      std::cout << "Error in Accepting new connections." << std::endl;
      continue;
    }
    std::cout << "Connection Accepted from client: "
              << network_convert_ip_n_to_p(client_addr.sin_addr.s_addr, 0)
              << "," << htons(client_addr.sin_port);
  }
}

std::shared_ptr<TcpServerControllerInterface>
TcpNewConnectionAcceptor::tcp_ctrlr() const {
  return tcp_ctrlr_;
}

std::shared_ptr<TcpServerControllerInterface> &
TcpNewConnectionAcceptor::tcp_ctrlr() {
  return tcp_ctrlr_;
}