#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "utils.cpp"

using namespace std;

int main(){

    string filename = inputString("File name");

    int main_sleep = inputInt("Main sleep");
    int fork_sleep = inputInt("Fork sleep");
    int vfork_sleep = inputInt("Vfork sleep");

    char *argv[] = { 
        "/home/sergey/Рабочий стол/linux_labs/lab3/exec",
        0
        };
    
    ofstream file(filename);
    file << "main - " << to_string(main_sleep) << " seconds"  << endl;
    file << "fork - " << to_string(fork_sleep) << " seconds" << endl;
    file << "vfork - " << to_string(vfork_sleep) << " seconds"  << endl;

    if(fork() == 0){
        sleep(fork_sleep);
        writeAttributes("fork",filename);
        exit(1);
    }

    if (vfork() == 0) {
            sleep(vfork_sleep);
            writeAttributes("vfork",filename);

            if(execv(argv[0], argv) == -1){
                exit(1);
            }
    } else {
        sleep(main_sleep);
        writeAttributes("main", filename);
    }
    
    file.close();
    return 0;
}