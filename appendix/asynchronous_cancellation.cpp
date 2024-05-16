#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

constexpr int N_SLAVES = 5;

pthread_t slaves[N_SLAVES];

void memory_cleanup_handler(void *arg) {
  std::cout << __FUNCTION__ << " invoked ..." << std::endl;
  free(arg);
}

void file_cleanup_handler(void *arg) {
  std::cout << __FUNCTION__ << " invoked ..." << std::endl;
  fclose((FILE *) arg);
}

void * write_into_file(void *arg) {
  char file_name[64];
  char string_to_write[64];
  int len, count = 0;

  pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, 0);
  pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, 0);

  int *thread_id = (int *)arg;
  pthread_cleanup_push(memory_cleanup_handler, arg);

  sprintf(file_name, "thread_%d.txt", *thread_id);

  FILE *fptr = fopen(file_name, "w");

  if (!fptr) {
    std::cout << "Error: Could not open log file " << file_name << std::endl;
    return nullptr;
  }
  pthread_cleanup_push(file_cleanup_handler, fptr);

  int itr = 0;
  while (true) {
    len = sprintf (string_to_write, "%d : I am thread %d\n", count++, *thread_id);
    fwrite(string_to_write, sizeof(char), len, fptr);
    fflush(fptr);
    sleep(1);
  }

  pthread_cleanup_pop(0);
  pthread_cleanup_pop(0);

  return nullptr;
}

int main (int argc, char **argv) {
  int i;
  int *thread_id = nullptr;

  for (int i = 0; i < N_SLAVES; ++i) {
    thread_id = new int(i);
    pthread_create(&slaves[i], nullptr, write_into_file, thread_id);
  }

  int choice, thread_num;

  while(true) {
    std::cout << "1. cancel the thread" << std::endl;
    std::cin >> choice;
    std::cout << "Enter slave thread id [0-" << N_SLAVES - 1 << "] :" << std::endl;
    std::cin >> thread_num;

    if (thread_num < 0 || thread_num >= N_SLAVES) {
      std::cout << "Invalid Thread id" << std::endl;
      exit(0);
    }
    
    switch (choice) {
      case 1:
        pthread_cancel(slaves[thread_num]);
        break;
      default:
        continue;
    }
  }

  return 0;
}