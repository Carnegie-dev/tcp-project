#ifndef __TCPCLIENTSERVICEMANAGERINTERFACE__
#define __TCPCLIENTSERVICEMANAGERINTERFACE__

class TcpClientServiceManagerInterface {
public:
  ~TcpClientServiceManagerInterface() = default;

  virtual void StartTcpClientServiceManagerThread() = 0;
};

#endif