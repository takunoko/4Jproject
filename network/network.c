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

#include "network.h"

// 戻り値としてfdが返される
// このfdに対してreadとかwriteを行うことによって通信を行える。
int init_client(void){
	struct sockaddr_in addr;
	struct hostent *hp;
	int    fd;
	int    len;

	char s_name[20] = "localhost";

	// サーバー名入力->接続
	// localhostでとりあえず固定している　
	// printf("Server Name : ");
	// scanf("%s",s_name);

	// ソケットを作る。このソケットはINETドメインで、ストリーム型ソケット。
	if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return 1;
	}

	// addrの中身を0にしておかないと、bind()でエラーが起こることがある
	bzero((char *)&addr, sizeof(addr));

	// ソケットの名前を入れておく
	if ((hp = gethostbyname(s_name)) == NULL) {
		perror("No such host");
		return 1;
	}

	bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	// サーバーとの接続を試みる。これが成功するためには、サーバーがすでに
	// このアドレスをbind()して、listen()を発行していなければならない。
	if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
		perror("connect");
		return 1;
	}

	return fd;
}

int init_server(void){
	int    i;
	int    fd1, fd2;
	struct sockaddr_in    saddr;
	struct sockaddr_in    caddr;
	char   buf[1024];

	/*
	 * ソケットを作る。このソケットはUNIXドメインで、ストリーム型ソケット。
	 */
	if ((fd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		return 1;
	}

	/*
	 * saddrの中身を0にしておかないと、bind()でエラーが起こることがある
	 */
	bzero((char *)&saddr, sizeof(saddr));

	/*
	 * ソケットの名前を入れておく
	 */
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(PORT);

	/*
	 * ソケットにアドレスをバインドする。
	 */
	if (bind(fd1, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
		perror("bind");
		return 1;
	}

	/*
	 * listenをソケットに対して発行する
	 */
	if (listen(fd1, 1) < 0) {
		perror("listen");
		return 1;
	}

	return fd1;
}
