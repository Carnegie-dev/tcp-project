#include "TcpServerController.h"

#include <iostream>

#include "network_utils/network_utils.h"

TcpServerController::TcpServerController(std::string ip_addr, uint16_t port_no,
                                         std::string name) {
  this->ip_addr() = network_convert_ip_p_to_n(ip_addr.c_str());
  this->port_no() = port_no;
  this->name() = name;
}

void TcpServerController::Start() {
  /* Start the CRS thread, DRS thread and initialize the DBMS */
  this->tcp_client_db_mgr()->StartTcpClientDBMgrInit();
  this->tcp_client_svc_mgr()->StartTcpClientServiceManagerThread();
  this->tcp_new_conn_acc()->StartTcpNewConnectionAcceptorThread();

  std::cout << "Tcp Server is Up and Running ["
            << network_convert_ip_n_to_p(this->ip_addr(), 0) << ","
            << this->port_no() << "]" << std::endl
            << "OK" << std::endl;
}

void TcpServerController::End() {}

uint32_t TcpServerController::ip_addr() const { return ip_addr_; }

uint16_t TcpServerController::port_no() const { return port_no_; }

std::string TcpServerController::name() const { return name_; }

uint32_t &TcpServerController::ip_addr() { return ip_addr_; }

uint16_t &TcpServerController::port_no() { return port_no_; }

std::string &TcpServerController::name() { return name_; }

std::shared_ptr<TcpClientDBManagerInterface>
TcpServerController::tcp_client_db_mgr() const {
  return tcp_client_db_mgr_;
}

std::shared_ptr<TcpClientServiceManagerInterface>
TcpServerController::tcp_client_svc_mgr() const {
  return tcp_client_svc_mgr_;
}

std::shared_ptr<TcpNewConnectionAcceptorInterface>
TcpServerController::tcp_new_conn_acc() const {
  return tcp_new_conn_acc_;
}

std::shared_ptr<TcpClientDBManagerInterface> &
TcpServerController::tcp_client_db_mgr() {
  return tcp_client_db_mgr_;
}

std::shared_ptr<TcpClientServiceManagerInterface> &
TcpServerController::tcp_client_svc_mgr() {
  return tcp_client_svc_mgr_;
}

std::shared_ptr<TcpNewConnectionAcceptorInterface> &
TcpServerController::tcp_new_conn_acc() {
  return tcp_new_conn_acc_;
}