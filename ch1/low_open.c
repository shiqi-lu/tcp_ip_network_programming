#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main()
{
    char buf[] = "Let's go!\n";
    int fd;

    // O_CREAT | O_WRONLY | O_TRUNC 是文件打开模式，将创建新文件，并且只能写
    // 如存在 data.txt 文件，则清空文件中的全部数据
    fd = open("data.txt", O_CREAT|O_WRONLY|O_TRUNC);
    if (fd == -1) {
        error_handling("open() error!");
    }
    printf("file descriptor: %d \n", fd);

    //
    if (write(fd, buf, sizeof(buf)) == -1) {
        error_handling("write() error!");
    }
    close(fd);

    return 0;
}
