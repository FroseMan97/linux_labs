#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.cpp"

using namespace std;

int main(){

    string filename = inputString("File name");

    int fork_sleep = inputInt("Fork sleep");
    int vfork_sleep = inputInt("Vfork sleep");
    int exec_sleep = inputInt("Exec sleep");

    char _param_exec_sleep[64];
    char _param_file_name[64];

    sprintf(_param_exec_sleep,"%d",exec_sleep);
    sprintf(_param_file_name,"%s", filename.c_str());

    char *argv[] = { 
        "/home/sergey/Рабочий стол/linux_labs/lab3/exec", 
        _param_exec_sleep,
        _param_file_name, 
        0
        };
    
    ofstream file(filename);
    file << "fork - " << to_string(fork_sleep) << " seconds" << endl;
    file << "vfork - " << to_string(vfork_sleep) << " seconds"  << endl;
    file << "exec - " << to_string(exec_sleep) << " seconds"  << endl << endl;

    if(fork() == 0){
        sleep(fork_sleep);
        writeAttributes("fork",filename);
        exit(1);
    }
    if (vfork() == 0) {
        sleep(vfork_sleep);
        writeAttributes("vfork",filename);

        execv(argv[0], argv);

        perror("exec error");
        exit(-1);
    }
    file.close();
    return 0;
}