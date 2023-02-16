#include "unp.h"

void str_cli(FILE *fp, int sockfd) {
    int maxfdp1, stdineof;
    char sendline[MAXLEN], recvline[MAXLEN];
    stdineof = 0;
    fd_set rset;
    FD_ZERO(&rset); // ファイルディスクリプタセットを削除する
    for(; ;) {
        if (stdineof == 0) FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;

        if (select(maxfdp1, &rset, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(1);
        }

        if (FD_ISSET(sockfd, &rset)) {
            if (readline(sockfd, recvline, sizeof(recvline)) == 0) {
                if (stdineof == 1) return;
                else {
                    fputs("str_cli: server terminated prematurely\n", stderr);
                    return;
                }
            }
            fputs(recvline, stdout);
        }
        if (FD_ISSET(fileno(fp), &rset)) {
            if (fgets(sendline, MAXLEN, fp) == NULL) { // input EOF
                stdineof = 1;
                shutdown(sockfd, SHUT_WR);
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            write(sockfd, sendline, strlen(sendline));
        }
    }
}