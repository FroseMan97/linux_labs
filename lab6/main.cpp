#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <iostream>
#include <chrono>
#include <ctime>

using namespace std;

int iteration = 0;
int number_of_starts;
int period;

void catch_signal(int ignored) {
    if(fork() == 0){
        auto start = chrono::system_clock::now();
        time_t start_time = chrono::system_clock::to_time_t(start);
        auto end = std::chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end-start;
        printf("Дочерний процесс[%d] - %d\nStart time: %sElapsed time: %f\n", 
            iteration,
            getpid(),
            ctime(&start_time),
            elapsed_seconds.count()
            );
        exit(0);
    }
     iteration++;
}

void start_timer(int interval) {
  struct itimerval it;
  struct sigaction sa;
  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = catch_signal;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  sigaction(SIGPROF, &sa, NULL);
  memset(&it, 0, sizeof(it));
  it.it_interval.tv_sec = interval;
  it.it_value.tv_sec = interval;
  setitimer(ITIMER_PROF, &it, NULL);
}

int main (int argc, const char **argv) {
    cout << "Количество запусков = ";
    cin >> number_of_starts;
    cout << "Период = ";
    cin >> period;
    auto start = chrono::system_clock::now();
        time_t start_time = chrono::system_clock::to_time_t(start);
    start_timer(period);
    if(iteration == number_of_starts){
        exit(0);
    }
    while(1);
    auto end = std::chrono::system_clock::now();
        chrono::duration<double> elapsed_seconds = end-start;
        printf("[Main]Start time: %sElapsed time: %f\n", 
            ctime(&start_time),
            elapsed_seconds.count()
            );
    return 0;
}