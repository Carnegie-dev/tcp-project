#ifndef __TCPNEWCONNECTIONACCEPTORINTERFACE__
#define __TCPNEWCONNECTIONACCEPTORINTERFACE__

#include <memory>

class TcpServerControllerInterface;

class TcpNewConnectionAcceptorInterface {
public:
  ~TcpNewConnectionAcceptorInterface() = default;

  virtual std::shared_ptr<TcpServerControllerInterface> tcp_ctrlr() const = 0;
  virtual std::shared_ptr<TcpServerControllerInterface> &tcp_ctrlr() = 0;

  virtual void StartTcpNewConnectionAcceptorThread() = 0;
  virtual void StartTcpNewConnectionAcceptorThreadInternal() = 0;
};

#endif