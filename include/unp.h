//多重インクルード防止
#ifndef UNP_H 
#define UNP_H

//-------------------------------------------------
//ヘッダファイルのインクルード
//-------------------------------------------------
#include<stdio.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include<signal.h>
#include<sys/wait.h>
#include<stdbool.h>

//-------------------------------------------------
// マクロ定義
//-------------------------------------------------
#define SERV_IP (0x7F000001)
#define SERV_PORT (9877)
#define LISTENQ (5)
#define MAXLEN (100000)

//-------------------------------------------------
//型定義
//-------------------------------------------------
typedef struct sockaddr SA;

//-------------------------------------------------
//プロトタイプ宣言
//-------------------------------------------------
ssize_t readline(int fd, char *vptr, size_t maxlen);
void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);
int max(int a, int b);
void sig_child(int signo);

#endif