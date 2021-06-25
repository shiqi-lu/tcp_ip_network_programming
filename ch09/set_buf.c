#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>

void error_handling(char * message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
    int sock;
    int snd_buf = 1024*3, rcv_buf = 1024*3;
    int state;
    socklen_t len;

    sock = socket(PF_INET, SOCK_STREAM, 0);
    // 更改 I/O 接收缓冲大小
    state = setsockopt(sock, SOL_SOCKET, SO_RCVBUF, (void *)&rcv_buf, sizeof(rcv_buf));
    if (state) {
        error_handling("setockopt() error!");
    }

    // 更改 I/O 发送缓冲大小
    state = setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (void *)&snd_buf, sizeof(snd_buf));
    if (state) {
        error_handling("setockopt() error!");
    }

    len = sizeof(snd_buf);
    // 读取 I/O 发送缓冲大小
    state = getsockopt(sock, SOL_SOCKET, SO_SNDBUF,
                       (void *)&snd_buf, &len);
    if (state) {
        error_handling("getsockopt() error");
    }
    printf("Output buffer size: %d\n", snd_buf);

    len = sizeof(rcv_buf);
    // 读取 I/O 接收缓冲大小
    state = getsockopt(sock, SOL_SOCKET, SO_RCVBUF,
                       (void *)&rcv_buf, &len);
    if (state) {
        error_handling("getsockopt() error");
    }
    printf("Input buffer size: %d\n", rcv_buf);

    return 0;
}
