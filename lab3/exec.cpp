#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.cpp"

using namespace std;

int main(int argc, char *argv[]){
    if(argv[1] == nullptr || argv[2] == nullptr){return -1;}
    int sleep_value = atoi(argv[1]);
    string filename = argv[2];
    sleep(sleep_value);
    writeAttributes("exec",filename);
    return 3;
}

