#include <iostream>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

pthread_t sub_thread_1;
pthread_t sub_thread_2;

void * thread_fn_callback(void *arg) {
  int id = *(int *)(arg);
  //free(arg);
  int rc = 0;
  while (rc < id) {
    std::cout << "Thread " << id << " is running." << std::endl;
    sleep(1);
    ++rc;
  }

  int *res = new int;
  *res = id * id;
  
  return (void *)(res);
}

void thread_create(pthread_t *thread, int id) {
  pthread_attr_t attr;
  pthread_attr_init(&attr);

  int *_id = new int;
  *_id = id;

  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
  pthread_create(thread, &attr, thread_fn_callback, (void *)_id);
}

int main(int argc, char **argv) {
  void *result_1, *result_2;

  int id1 = 8, id2 = 6;
  thread_create(&sub_thread_1, id1);
  thread_create(&sub_thread_2, id2);

  std::cout << "Main fn blocked on pthread join for thread with th_id = " << id2 << std::endl;
  pthread_join(sub_thread_2, &result_2);
  if (result_2) {
    std::cout << "Return result from thread 2 = " << *(int *)(result_2) << std::endl;
    free(result_2);
    result_2 = nullptr;
  }

  std::cout << "Main fn blocked on pthread join for thread with th_id = " << id1 << std::endl;
  pthread_join(sub_thread_1, &result_1);
  if (result_1) {
    std::cout << "Return result from thread 1 = " << *(int *)(result_1) << std::endl;
    free(result_1);
    result_1 = nullptr;
  }

  return 0;
}