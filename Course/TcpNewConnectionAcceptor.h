#ifndef __TCPNEWCONNECTIONACCEPTOR__
#define __TCPNEWCONNECTIONACCEPTOR__

#include <pthread.h>

#include "TcpNewConnectionAcceptorInterface.h"
#include "TcpServerControllerInterface.h"

class TcpNewConnectionAcceptor : public TcpNewConnectionAcceptorInterface {
public:
  TcpNewConnectionAcceptor(const std::shared_ptr<TcpServerControllerInterface>& );

  ~TcpNewConnectionAcceptor() = default;

  std::shared_ptr<TcpServerControllerInterface> tcp_ctrlr() const override;
  std::shared_ptr<TcpServerControllerInterface> &tcp_ctrlr() override;

  void StartTcpNewConnectionAcceptorThread() override;
  void StartTcpNewConnectionAcceptorThreadInternal() override;

private:
  int accept_fd;
  std::shared_ptr<TcpServerControllerInterface> tcp_ctrlr_{nullptr};
  std::shared_ptr<pthread_t> accept_new_conn_thread;
};

#endif