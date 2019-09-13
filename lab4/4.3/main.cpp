#include <iostream>
#include <fstream>
#include <pthread.h>
using namespace std;
// 1 поток - нечетные строки
// 2 поток - четные
pthread_mutex_t lock;
ofstream out_1, out_2;
 ifstream in;
static void * start_thread_1(void *arg);
static void * start_thread_2(void *arg);
string line;
int main(){
    pthread_mutex_init(&lock,NULL);
    in.open("/home/sergey/Рабочий стол/linux_labs/lab4/4.3/in.txt");
    out_1.open("/home/sergey/Рабочий стол/linux_labs/lab4/4.3/out_1.txt");
    out_2.open("/home/sergey/Рабочий стол/linux_labs/lab4/4.3/out_2.txt");
    int linesCount = 0;
    if(!(in.is_open() && out_1.is_open() && out_2.is_open()))
        perror("Не удалось открыть файлы");
    pthread_t thread_1, thread_2;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    while(getline(in, line)){
        pthread_mutex_lock(&lock);
        linesCount++;
        if(linesCount % 2 != 0){
            pthread_create(&thread_1,&attr,&start_thread_1,&line);
        }
        else{
            pthread_create(&thread_2,&attr,&start_thread_2,&line);
        }
        pthread_mutex_unlock(&lock);
    }
    in.close();
    out_1.close();
    out_2.close();
    return 0;
}
static void * start_thread_1(void *arg){
    string line = *((string *) arg);
    out_1 << line << endl;
    pthread_exit(0);
}
static void * start_thread_2(void *arg){
    string line = *((string *) arg);
    out_2 << line << endl;
    pthread_exit(0);
}
