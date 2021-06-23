#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/select.h>

#define BUF_SIZE 30

int main()
{
    fd_set reads, temps;
    int result, str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;
    
    // 初始化变量
    FD_ZERO(&reads);
    // 将文件描述符0对应的位设置为1
    // 即监视标准输入的变化
    FD_SET(0, &reads);

    while (1) {
        // 将准备好的fd_set变量reads的内容复制到temps变量，
        // 因为调用select函数后，除发生变化的文件描述符对应位外，
        // 剩下的位将初始化为0。为了记住初始化值，必须复制
        temps = reads;
        // 设置select函数的超时，因调用select后，timeval的成员的值
        // 将被替换为超时前剩余时间。所以在调用select前均需初始化
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        // 如果控制台输入数据会返回大于0的整数
        // 如果没有输入数据而引发超时，返回0
        result = select(1, &temps, 0, 0, &timeout);
        if (result == -1) {
            puts("select() error!");
            break;
        } else if (result == 0) {
            puts("Time-out!");
        } else {
            if (FD_ISSET(0, &temps)) {
                // 验证发生变化的文件描述符是否为标准输入
                // 若是，从标准输入读取数据并向控制台输出
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("message from concole: %s", buf);
            }
        }
    }

    return 0;
}
