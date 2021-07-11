#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

// 这里的 arg 参数是 pthread_create 的第 4 个参数
void * thread_main(void * arg)
{
    int i;
    int cnt = *((int *)arg);
    for (i = 0; i < cnt; ++i) {
        sleep(1);
        puts("running thread");
    }
    return NULL;
}

int main(int argc, char * argv[])
{
    pthread_t t_id;
    int thread_param = 5;

    if (pthread_create(&t_id, 
                       NULL, 
                       thread_main, 
                       (void *)&thread_param) != 0) {
        puts("thread_create() error");
        return -1;
    }
    // 为了延迟进程的终止时间
    sleep(10);
    puts("end of main");

    return 0;
}
