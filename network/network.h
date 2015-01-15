/*
 * mserver2.c
 *   クライアントからの接続要求を受け付けるサーバープログラム。
 *   大文字への変換はfork()で生成された子プロセスが行う。
 *   STREAM型のソケットを使う。
 */

// 共通して使う
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >の代わり */

// client側で使う
#include <netdb.h>

#define PORT 8765



int init_client(void);
int init_server(void);


