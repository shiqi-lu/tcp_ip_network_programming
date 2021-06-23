#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    int status;
    pid_t pid = fork();
    if (pid == 0) {
        // 推迟子进程的执行
        sleep(15);
        return 24;
    } else {
        // 调用waitpid 传递参数 WNOHANG
        // 这样之前有没有终止的子进程则返回0
        while (!waitpid(-1, &status, WNOHANG)) {
            sleep(3);
            puts("sleep 3 sec.");
        }
        if (WIFEXITED(status)) {
            printf("Child send %d \n", WEXITSTATUS(status));
        }
    }

    return 0;
}
