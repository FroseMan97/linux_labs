#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include "utils.cpp"

using namespace std;

int main(){

    string fileName = inputString("File name");
    int fork_sleep = inputInt("Fork sleep");
    int vfork_sleep = inputInt("Vfork sleep");
    int exec_sleep = inputInt("Exec sleep");

    char _param[64];
    sprintf(_param,"%d",exec_sleep);
    char *argv[] = { "/home/sergey/Рабочий стол/linux_labs/lab3/exec", _param, 0};

    if(fork() == 0){
        sleep(fork_sleep);
        showAttributes("fork");
        exit(0);
    }    
    if (vfork() == 0) {
        sleep(vfork_sleep);
        showAttributes("vfork");
        execv(argv[0], argv);
        perror("exec error");
    }
    return 0;
}