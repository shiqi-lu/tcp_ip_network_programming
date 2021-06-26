#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int sig)
{
    if (sig == SIGALRM) {
        puts("Time out!");
    }
    alarm(2);
}

int main()
{
    int i;

    // 为了注册信号处理函数，声明 sigaction 结构体变量
    // 并在 sa_handler 成员中保存函数指针值
    struct sigaction act;
    act.sa_handler = timeout;
    // sigemptyset 函数将 sa_mask 成员的所有位初始化为0
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    sigaction(SIGALRM, &act, 0);

    // 注册 SIGALRM 信号的处理器。
    // 调用 alarm 函数预约2秒后发生 SIGALRM 信号
    alarm(2);

    for (int i = 0; i < 3; ++i) {
        puts("wait...");
        sleep(100);
    }

    return 0;
}
