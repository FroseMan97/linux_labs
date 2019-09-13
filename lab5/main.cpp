#include <signal.h>
#include <iostream>

using namespace std;

void handler_sigsegv(int signum){
    printf("SIGSEGV(1) error (Нарушение защиты памяти)");
    signal(signum,SIG_DFL);
    exit(1);
}

void handler_sigfpe(int signum){
    printf("SIGFPE(2) error (Деление на ноль)");
    signal(signum,SIG_DFL);
    exit(2);
}

void fail_sigsegv(){
    int* ptr = 0x00000000;
    *ptr = 10;
}

void fail_sigfpe(){
    int x;
    x = 1/0;
}

int main(){
    signal(SIGSEGV, handler_sigsegv);
    signal(SIGFPE,handler_sigfpe);

    int code;
    cout << "Код(1 - SIGSEGV, 2 - SIGFPE): ";
    cin >> code;
    switch(code){
        case 2: fail_sigfpe(); break;
        case 1: fail_sigsegv(); break;
        default: cout << "(((\n"; break;
    }
    return 0;
}