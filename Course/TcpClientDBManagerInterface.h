#ifndef __TCPCLIENTDBMANAGERINTERFACE__
#define __TCPCLIENTDBMANAGERINTERFACE__

class TcpClientDBManagerInterface {
public:
  ~TcpClientDBManagerInterface() = default;

  virtual void StartTcpClientDBMgrInit() = 0;
};

#endif
