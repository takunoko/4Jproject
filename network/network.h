/*
 * mserver2.c
 *   クライアントからの接続要求を受け付けるサーバープログラム。
 *   大文字への変換はfork()で生成された子プロセスが行う。
 *   STREAM型のソケットを使う。
 */
#define PORT 8765

int init_client(void);
int init_server(void);
