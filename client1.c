#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <ctype.h>

#define SERV_PORT 4608

int main(int argc, char *argv[]) {
    int sockfd;
    struct sockaddr_in serv_addr;
    char str[BUFSIZ];

    // 参数检查
    if (argc != 3) {
        printf("please enter in following format\nUsage: %s <server_address> <port>\n", argv[0]);
        exit(1);
    }

    // 创建套接字
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 初始化服务器地址结构
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[2]));
    inet_pton(AF_INET, argv[1], &serv_addr.sin_addr);

    // 连接服务器
    connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

    // 读取用户输入
    printf("Please enter a message: ");
    fgets(str, BUFSIZ, stdin);

    // 向服务器发送数据
    write(sockfd, str, strlen(str));

    // 读取服务器返回的数据
    int n = read(sockfd, str, sizeof(str));

    // 转换成大写
    for (int i = 0; i < n; ++i) {
        str[i] = toupper(str[i]);
    }

    printf("\n receive %s from 192.168.18.8(server)\n", str);

    // 关闭套接字
    close(sockfd);

    return 0;
}
