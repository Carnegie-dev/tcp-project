#ifndef __TCPCLIENTDBMANAGER__
#define __TCPCLIENTDBMANAGER__

#include <list>
#include <memory>

#include "TcpClientDBManagerInterface.h"
#include "TcpServerControllerInterface.h"

class TcpClient;

class TcpClientDBManager : public TcpClientDBManagerInterface {

public:
  TcpClientDBManager(
      const std::shared_ptr<TcpServerControllerInterface> &tcp_ctrlr);

  ~TcpClientDBManager() = default;

  void StartTcpClientDBMgrInit() override;

private:
  std::list<std::shared_ptr<TcpClient>> tcp_client_dbs_;
  std::shared_ptr<TcpServerControllerInterface> tcp_ctrlr_{nullptr};
};

#endif
