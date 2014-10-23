/*
 * mserver2.c
 *   クライアントからの接続要求を受け付けるサーバープログラム。
 *   大文字への変換はfork()で生成された子プロセスが行う。
 *   STREAM型のソケットを使う。
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >の代わり */

#define PORT 8765

main()
{
    int    i;
    int    fd1, fd2;
    struct sockaddr_in    saddr;
    struct sockaddr_in    caddr;
    int    len;
    int    ret;
    char   buf[1024];
    int    pid;
    int    msglen;

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

    len = sizeof(caddr);
    /*
     * accept()により、クライアントからの接続要求を受け付ける。
     * 成功すると、クライアントと接続されたソケットのディスクリプタが
     * fd2に返される。このfd2を通して通信が可能となる。
     */
    for(;;){
	if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, &len)) < 0) {
	    perror("accept");
	    return 1;
	}
	/* 
	 *  fork()を使って作業専用のプロセスを作る
	 *  親プロセスは、次の接続要求を待つためにループし、
         *  新しく生成された子プロセスは大文字に変換する作業だけを行う
	 */  
	if ((pid = fork()) < 0) {
	    perror("fork");
	    return 1;
	} else if (pid == 0) {
	    /* fork()で新しく生成されたプロセスはこちら */
	    close(fd1);
	    ret = read(fd2, buf, 1024);
	    while (strcmp(buf, "quit\n") != 0) {
		/* bufの中の小文字を大文字に変換する */
		for (i=0; i < ret; i++) {
		    if (isalpha(buf[i]))
			buf[i] = toupper(buf[i]);
		}   
		/* 変換したデータをクライアントに送り返す */
		write(fd2, buf, 1024);
		ret = read(fd2, buf, 1024);
	    }
	    return 0;
	}
	/* 親プロセスはfd2を閉じて接続要求待ちのループに戻る */
	close(fd2);
    }
}


