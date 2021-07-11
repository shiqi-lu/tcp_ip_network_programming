#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

void * thread_main(void * arg)
{
    int i;
    int cnt = *((int *)arg);
    char * msg = (char *)malloc(sizeof(char)*50);
    strcpy(msg, "hello, I'm thread ~\n");

    for (i = 0; i < cnt; ++i) {
        sleep(1);
        puts("running thread");
    }
    return (void *)msg;
}

int main(int argc, char * argv[])
{
    pthread_t t_id;
    int thread_param = 5;
    void * thr_ret;

    if (pthread_create(&t_id,
                       NULL,
                       thread_main,
                       (void *)&thread_param) != 0) {
        puts("pthread_create() error");
        return -1;
    }

    // 注意此处获取返回值的方法
    // 注意返回值是 thread_main 函数内部动态分配的内存空间地址值
    if (pthread_join(t_id, &thr_ret) != 0) {
        puts("pthread_join() error");
        return -1;
    }

    printf("Thread return message: %s\n", (char *)thr_ret);
    free(thr_ret);
    return 0;
}
