#include "unp.h"

/*
sockfdのファイル内容を標準出力とソケットファイルにそれぞれ書き込む

Parameter
---------
sockfd: ソケットディスクリプタ
*/
void str_echo(int sockfd) {
    ssize_t n;
    char line[MAXLEN];
    for(; ;) {
        if ( (n = readline(sockfd, line, sizeof(line))) == 0) {
            return;
        }
        write(STDOUT_FILENO, line, n);
        write(sockfd, line, n);
    }
}