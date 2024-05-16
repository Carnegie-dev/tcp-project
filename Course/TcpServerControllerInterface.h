#ifndef __TCPSERVERCONTROLLER_INTERFACE__
#define __TCPSERVERCONTROLLER_INTERFACE__

#include <memory>
#include <stdint.h>
#include <string>

class TcpClientDBManagerInterface;
class TcpClientServiceManagerInterface;
class TcpNewConnectionAcceptorInterface;

class TcpServerControllerInterface {
public:
  ~TcpServerControllerInterface() = default;

  virtual std::shared_ptr<TcpClientDBManagerInterface>
  tcp_client_db_mgr() const = 0;
  virtual std::shared_ptr<TcpClientServiceManagerInterface>
  tcp_client_svc_mgr() const = 0;
  virtual std::shared_ptr<TcpNewConnectionAcceptorInterface>
  tcp_new_conn_acc() const = 0;

  virtual std::shared_ptr<TcpClientDBManagerInterface> &tcp_client_db_mgr() = 0;
  virtual std::shared_ptr<TcpClientServiceManagerInterface> &
  tcp_client_svc_mgr() = 0;
  virtual std::shared_ptr<TcpNewConnectionAcceptorInterface> &
  tcp_new_conn_acc() = 0;

  virtual void Start() = 0;
  virtual void End() = 0;

  virtual uint32_t ip_addr() const = 0;
  virtual uint16_t port_no() const = 0;
  virtual std::string name() const = 0;

  virtual uint32_t &ip_addr() = 0;
  virtual uint16_t &port_no() = 0;
  virtual std::string &name() = 0;
};

#endif