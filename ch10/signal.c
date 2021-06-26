#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// 信号处理器(Handler)
void timeout(int sig)
{
    if (sig == SIGALRM) {
        puts("Time out!");
    }
    // 每隔2秒重复产生 SIGALRM 信号
    alarm(2);
}

void keycontrol(int sig)
{
    if (sig == SIGINT) {
        puts("CTRL+C pressed");
    }
}

int main()
{
    int i;
    // 注册 SIGALRM、SIGINT 信号及相应处理器
    signal(SIGALRM, timeout);
    signal(SIGINT, keycontrol);
    alarm(2);

    for (i = 0; i < 3; ++i) {
        puts("wait...");
        sleep(100);
    }

    return 0;
}
