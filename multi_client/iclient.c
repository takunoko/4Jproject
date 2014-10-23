#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 8765

main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    struct hostent *hp;
    int    fd;
    int    len;
    char   buf[1024];
    int    ret;



    if (argc != 2){
	printf("Usage: iclient SERVER_NAME\n");
	return 1;
    }

    // ソケットを作る。このソケットはINETドメインで、ストリーム型ソケット。
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    // addrの中身を0にしておかないと、bind()でエラーが起こることがある
    bzero((char *)&addr, sizeof(addr));

    // ソケットの名前を入れておく
    if ((hp = gethostbyname(argv[1])) == NULL) {
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

    // 入力されたデータをソケットに書き込んでサーバーに送り、
    // サーバーが変換して送ってきたデータを読み込む。
    while (fgets(buf, 1024, stdin)) {
        write(fd, buf, 1024);
        ret = read(fd, buf, 1024);
	buf[ret] = '\0';
        //write(1, buf, ret);
        printf("%s",buf);
    }
    close(fd);
    return 0;
}



