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
    int tcp_sock, udp_sock;
    int sock_type;
    socklen_t optlen;
    int state;

    optlen = sizeof(sock_type);
    // 分别生成TCP、UDP套接字
    tcp_sock = socket(PF_INET, SOCK_STREAM, 0);
    udp_sock = socket(PF_INET, SOCK_DGRAM, 0);
    // 输出创建TCP、UDP套接字时传入的SOCK_STREAM、SOCK_DGRAM
    printf("SOCK_STREAM: %d\n", SOCK_STREAM);
    printf("SOCK_DGRAM: %d\n", SOCK_DGRAM);

    // 获取套接字类型信息
    // 如果是TCP套接字，将获得SOCK_STREAM常数值1
    state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, 
                       (void*)&sock_type, &optlen);
    if (state) {
        error_handling("getsockopt() error!");
    }
    printf("Socket type one: %d\n", sock_type);

    // 如果是UDP套接字，则获得SOCK_DGRAM的常数值2
    state = getsockopt(tcp_sock, SOL_SOCKET, SO_TYPE, 
                       (void*)&sock_type, &optlen);
    if (state) {
        error_handling("getsockopt() error!");
    }
    printf("Socket type two: %d\n", sock_type);

    return 0;
}
