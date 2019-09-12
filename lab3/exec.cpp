#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include "utils.cpp"

using namespace std;

int main(int argc, char *argv[]){
    if(argv[1] == nullptr){return -1;}
    int sleep_value = atoi(argv[1]);
    sleep(sleep_value);
    cout << endl << "exec" << endl;
    showAttributes("exec");
    return 3;
}

