#include "TcpClientServiceManager.h"

TcpClientServiceManager::TcpClientServiceManager(
    const std::shared_ptr<TcpServerControllerInterface> &tcp_ctrlr)
    : tcp_ctrlr_(tcp_ctrlr) {}

void TcpClientServiceManager::StartTcpClientServiceManagerThread() {}