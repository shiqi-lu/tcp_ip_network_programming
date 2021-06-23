#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>

void error_handling(char *message)
{
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

int main(int argc, char *argv[])
{
    int i;
    struct hostent * host;
    if (argc != 2) {
        printf("Usage : %s <addr>\n", argv[0]);
        exit(1);
    }

    host = gethostbyname(argv[1]);
    if (!host) {
        error_handling("gethost... error");
    }

    // 输出官方域名
    printf("Official name: %s \n", host->h_name);
    
    // 输出除官方域名以外的域名
    for (i = 0; host->h_aliases[i]; ++i) {
        printf("Aliases %d: %s \n", i+1, host->h_aliases[i]);
    }
    
    // 看看是不是ipv4
    printf("Address type: %s \n",
           (host->h_addrtype == AF_INET)? "AF_INET": "AF_INET6");
    
    // 输出ip地址信息 
    for (i = 0; host->h_addr_list[i]; ++i) {
        printf("IP addr %d: %s \n", i+1,
               inet_ntoa(*(struct in_addr *)host->h_addr_list[i]));
    }

    return 0;
}