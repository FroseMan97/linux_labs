#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>

using namespace std;

int inputInt(string message){
    int integer=0;
    cout << (message + " = ");
    cin >> integer;
    return integer;
}

string inputString(string message){
    string str = "";
    cout << (message + " = ");
    cin >> str;
    cout << endl;
    return str;
}

void showAttributes(const char *name){
    cout << endl << endl << name << endl;
    pid_t pid = getpid();
    cout << "Идентификатор процесса " << pid << endl;
    cout << "Идентификатор предка " << getppid() << endl;
    cout << "Идентификатор сессии процесса " << getsid(pid) << endl;
    cout << "Идентификатор группы процессов " << getpgid(pid) << endl;
    cout << "Реальный дентификатор пользователя " << getuid() << endl;
    cout << "Эффективный идентификатор пользователя " << geteuid() << endl;
    cout << "Реальный групповой идентификатор " << getgid() << endl;
    cout << "Эффективный групповой идентификатор " << getegid() << endl;
    cout << endl;
}