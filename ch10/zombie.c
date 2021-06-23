#include <stdio.h>
#include <unistd.h>

int main()
{
    pid_t pid = fork();
    if (pid == 0) {
        //子进程
        puts("Hi, I am a child process");
    } else {
        // 父进程
        // 输出子进程ID，可通过该值查看子进程状态（是否为僵尸进程）
        printf("Child Process ID: %d \n", pid);
        // 如果父进程终止，处于僵尸状态的子进程将同时销毁
        // 因此延缓父进程的执行以验证僵尸进程
        sleep(30);
    }

    if (pid == 0) {
        puts("End child proess");
    } else {
        puts("End parent process");
    }

    return 0;
}
