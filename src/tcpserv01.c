#include "unp.h"

int main(void) {

    //変数宣言
    char line[MAXLEN]; // ソケットファイルから読み込むときのバッファ
    int maxi, maxfd, read_length, listenfd, connfd, sockfd;;
    int nreadby, client[FD_SETSIZE], client_index;
    struct sockaddr_in addr, chiaddr;
    socklen_t chilen;
    fd_set allset, rset;

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

    maxfd = listenfd;
    maxi = -1;
    for (int i = 0; i < FD_SETSIZE; i++) {
        client[i] = -1;
    }
    FD_ZERO(&allset); //selectの初期化
    FD_SET(listenfd, &allset);

    for (; ;) {
        rset = allset;
        nreadby = select(maxfd + 1, &rset, NULL, NULL, NULL);
        if (nreadby == -1) { //エラー処理
            perror("select");
            exit(1);
        }
        if (FD_ISSET(listenfd, &rset)) { // 新しいクライアントから接続がきた時
            chilen = sizeof(chiaddr);
            connfd = accept(listenfd, (SA *)&chiaddr, &chilen);
            for (client_index = 0; client_index < FD_SETSIZE; client_index++ ){
                if (client[client_index] < 0) {
                    printf("connect Success\n");
                    printf("Socket discripter is %d\n", connfd);
                    client[client_index] = connfd;
                    break;
                }
            }
            FD_SET(connfd, &allset); //ソケットディスクリプタを追加
            if (client_index == FD_SETSIZE) { // 接続しているクライアントが限界まで達したとき
                fputs("too many clients", stderr);
                exit(1);
            }
            if (connfd > maxfd) { // maxfdの更新
                maxfd = connfd;
            }
            if (client_index > maxi) {
                maxi = client_index;
            }        
            if (--nreadby <= 0) { // 読み出し可能なファイルがなくなったとき
                continue;
            }                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               
        } 
        for (int i = 0; i < FD_SETSIZE; i++ ) {
            if ((sockfd = client[i]) < 0) continue;
            if (FD_ISSET(sockfd, &rset)) {
                if ((read_length = readline(client[i], line, sizeof(line))) == 0) {
                    close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                    printf("disconnect Syccess\n");
                    printf("Socket discripter is %d\n", sockfd);
                } else {
                    write(STDOUT_FILENO, line, read_length);
                    write(sockfd, line, read_length);
                }
                if (--nreadby <= 0) continue;
            }
        }
    }
}