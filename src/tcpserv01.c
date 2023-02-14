#include "unp.h"

// Sigfunc *signal(int signo, Sigfunc *func);
void sig_child(int signo);

int main(void) {

    //変数宣言
    struct sockaddr_in addr, chiaddr;
    socklen_t chilen;
    int listenfd, connfd, childpid;

    /*
    step1
    ソケットファイルを作成する
    */
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1) {
        perror("socket");
        return 1;
    }
    printf("socket: Success\n");

    /*
    step2
    ソケットにプロトコルアドレスをバインドする
    */
    addr.sin_addr.s_addr = htonl(SERV_IP);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERV_PORT);

    if (bind(listenfd, (SA *)&addr, sizeof(addr))) {
        perror("bind");
        return 1;
    }
    printf("bind: Success\n");

    /*
    step3
    ソケットをパッシブソケットにする
    */
    if (listen(listenfd, LISTENQ)) {
        perror("listen");
        return 1;
    }
    printf("listen: Success\n");

    signal(SIGCHLD, sig_child);

    for(; ;) {
        chilen = sizeof(chiaddr);
        connfd = accept(listenfd, (SA *)&chiaddr, &chilen);

        if (connfd == -1) { // 接続に失敗した時
            if (errno == EINTR) continue;
            else {
                perror("accept");
                return 1;
            }
        } 

        if ( (childpid = fork()) == 0) {
            close(listenfd);
            str_echo(connfd);
            close(connfd);
            exit(0);
        }
        close(connfd);
    } 
}