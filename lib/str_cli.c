#include "unp.h"

void str_cli(FILE *fp, int sockfd) {
    int maxfdp1;
    char sendline[MAXLEN], recvline[MAXLEN];
    fd_set rset;
    FD_ZERO(&rset); // ファイルディスクリプタセットを削除する
    for(; ;) {
        FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;

        if (select(maxfdp1, &rset, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }

        if (FD_ISSET(sockfd, &rset)) {
            if (readline(sockfd, recvline, sizeof(recvline)) == 0) {
                fputs("str_cli: server terminated prematurely\n", stderr);
                return;
            }
            fputs(recvline, stdout);
        }
        if (FD_ISSET(fileno(fp), &rset)) {
            if (fgets(sendline, MAXLEN, fp) == NULL) { // input EOF
                return;
            }
            write(sockfd, sendline, strlen(sendline));
        }
    }
}