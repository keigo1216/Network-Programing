#include "unp.h"

int main(void) {

    //変数の宣言
    int sockfd;
    struct sockaddr_in servaddr;

    /*
    step1
    ソケットファイルを作成する
    */
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        perror("socket");
        return 1;
    }
    printf("socket: Success\n");

    /*
    step2
    サーバーとのコネクション確立
    */
    servaddr.sin_addr.s_addr = htonl(SERV_IP);
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    if(connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) == -1) {
        perror("connect");
        return 1;
    }
    printf("connetc: Success\n");

    str_cli(stdin, sockfd);
    // write(sockfd, "\0", sizeof("\0")); //EOFが入力されたら空文字を送って通信終了の合図

    // sleep(1);
    exit(0);
    // return 0;
}