#include "TcpServerController.h"
#include "TcpNewConnectionAcceptor.h"
#include "TcpClientServiceManager.h"
#include "TcpClientDBManager.h"

int main (int argc, char **argv) {
  auto server1 = std::make_shared<TcpServerController>("127.0.0.1", 40000, "Default TCP Server");

  server1->tcp_client_db_mgr() = std::make_shared<TcpClientDBManager>(server1);
  server1->tcp_client_svc_mgr() = std::make_shared<TcpClientServiceManager>(server1);
  server1->tcp_new_conn_acc() = std::make_shared<TcpNewConnectionAcceptor>(server1);

  server1->Start();

  scanf("\n");

  return 0;
}