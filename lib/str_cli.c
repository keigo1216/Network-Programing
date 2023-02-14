#include "unp.h"

void str_cli(FILE *fp, int sockfd) {
    char sendline[MAXLEN], recvline[MAXLEN];
    while (fgets(sendline, MAXLEN, fp) != NULL) {
        write(sockfd, sendline, strlen(sendline));
        if (readline(sockfd, recvline, sizeof(recvline)) == 0) {
            fputs("str_cli: server terminated prematurely\n", stderr);
            return;
        }
        fputs(recvline, stdout);
    }
}