#ifndef __TCPSERVERCONTROLLER__
#define __TCPSERVERCONTROLLER__

#include <memory>
#include <stdint.h>
#include <string>

#include "TcpClientDBManagerInterface.h"
#include "TcpClientServiceManagerInterface.h"
#include "TcpNewConnectionAcceptorInterface.h"
#include "TcpServerControllerInterface.h"

class TcpServerController : public TcpServerControllerInterface {
public:
  /* Constructors and Destructors */
  TcpServerController(std::string ip_addr, uint16_t port_no, std::string name);

  std::shared_ptr<TcpClientDBManagerInterface>
  tcp_client_db_mgr() const override;
  std::shared_ptr<TcpClientServiceManagerInterface>
  tcp_client_svc_mgr() const override;
  std::shared_ptr<TcpNewConnectionAcceptorInterface>
  tcp_new_conn_acc() const override;

  std::shared_ptr<TcpClientDBManagerInterface> &tcp_client_db_mgr() override;
  std::shared_ptr<TcpClientServiceManagerInterface> &
  tcp_client_svc_mgr() override;
  std::shared_ptr<TcpNewConnectionAcceptorInterface> &
  tcp_new_conn_acc() override;

  void Start() override;
  void End() override;

  uint32_t ip_addr() const override;
  uint16_t port_no() const override;
  std::string name() const override;

  uint32_t &ip_addr() override;
  uint16_t &port_no() override;
  std::string &name() override;

private:
  uint32_t ip_addr_;
  uint16_t port_no_;
  std::string name_;

  std::shared_ptr<TcpClientDBManagerInterface> tcp_client_db_mgr_{nullptr};
  std::shared_ptr<TcpClientServiceManagerInterface> tcp_client_svc_mgr_{
      nullptr};
  std::shared_ptr<TcpNewConnectionAcceptorInterface> tcp_new_conn_acc_{nullptr};
};

#endif