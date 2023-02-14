#include "unp.h"

/*
ファイルディスクリプタfdの中身を最大maxlenまで読み込む
読み込んだ内容は参照わたしで渡されている第二引数に格納される

Parameter
---------
fd: 対象のファイルディスクリプタ
vptr: 文字列配列の先頭ポインタ
maxlen: 読み込む最大の行数

Return
------
-1: エラー
その他; 読み込んだ文字数
*/
ssize_t readline(int fd, char *vptr, size_t maxlen) {
    ssize_t rc;
    char buf, *ptr;
    ssize_t num_char = 0;
    ptr = vptr;

    while(1) {
        if (num_char > maxlen) return num_char; //読み込める最大まで達した時
        rc = read(fd, &buf, sizeof(buf));

        if (rc == -1) { //読み込みに失敗した時
            if (errno == EINTR) continue;
            perror("readline");
            return -1;
        } else if (rc == 0) { //ファイルの終端に達した時
            *ptr = '\0';
            return num_char;
        } else if (rc == 1) { //読み込みに成功した時
            if (buf == '\0') {
                return num_char;
            } else {
                *ptr++ = buf;
                num_char++;
                if (buf == '\n') {
                    *ptr = '\0';
                    return num_char;
                }
            }
        } else { //予期しないエラー
            perror("readline");
            return -1;
        }
    }
}