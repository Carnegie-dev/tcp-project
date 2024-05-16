#ifndef __TCPCLIENTSERVICEMANAGER__
#define __TCPCLIENTSERVICEMANAGER__

#include "TcpClientServiceManagerInterface.h"
#include "TcpServerControllerInterface.h"

class TcpClientServiceManager : public TcpClientServiceManagerInterface {
public:
  TcpClientServiceManager(
      const std::shared_ptr<TcpServerControllerInterface> &);

  ~TcpClientServiceManager() = default;

  void StartTcpClientServiceManagerThread() override;

private:
  std::shared_ptr<TcpServerControllerInterface> tcp_ctrlr_;
};

#endif