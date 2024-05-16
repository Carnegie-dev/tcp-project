#include "TcpClientDBManager.h"

TcpClientDBManager::TcpClientDBManager(
    const std::shared_ptr<TcpServerControllerInterface> &tcp_ctrlr)
    : tcp_ctrlr_(tcp_ctrlr) {}

void TcpClientDBManager::StartTcpClientDBMgrInit() {}