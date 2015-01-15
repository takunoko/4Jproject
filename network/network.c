#include "network.h"
// 戻り値としてfdが返される
// このfdに対してreadとかwriteを行うことによって通信を行える。
int init_client(void){
	struct sockaddr_in addr;
	struct hostent *hp;
	int    fd;
	int    len;

	char s_name[20];

	// サーバー名入力->接続
	printf("Server Name : ");
	scanf("%s",s_name);

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

int main(){
	char mode;
	char buf_clear;

	// Clientモードで使う変数
	char	c_buf[1024];
	int		c_ret;
	int		c_fd;

	// Serverモードで使う変数
	struct sockaddr_in	s_caddr;
	int s_len;
	int s_ret;
	int s_fd1, s_fd2;
	int s_pid;
	char s_buf[1024];
	int i;

	puts("You are server or Client ?");
	puts("Server: S, Client: C");
	scanf(" %c",&mode); // %cの前の空白でバッファをうまい感じにしてる

	if(mode == 's' || mode == 'S'){
		/*
		 * accept()により、クライアントからの接続要求を受け付ける。
		 * 成功すると、クライアントと接続されたソケットのディスクリプタが
		 * fd2に返される。このfd2を通して通信が可能となる。
		 */
		s_fd1 = init_server();

		s_len = sizeof(s_caddr);
		for(;;){
			if ((s_fd2 = accept(s_fd1, (struct sockaddr *)&s_caddr, &s_len)) < 0) {
				perror("accept");
				return 1;
			}
			/*
			 *  fork()を使って作業専用のプロセスを作る
			 *  親プロセスは、次の接続要求を待つためにループし、
			 *  新しく生成された子プロセスは大文字に変換する作業だけを行う
			 */
			if ((s_pid = fork()) < 0) {
				perror("fork");
				return 1;
			} else if (s_pid == 0) {
				/* fork()で新しく生成されたプロセスはこちら */
				/* 子プロセスに相当する */
				close(s_fd1);
				s_ret = read(s_fd2, s_buf, 1024);
				while (strcmp(s_buf, "quit¥n") != 0) { // 子プロセスはこの中を無限ループ
					/* s_bufの中の小文字を大文字に変換する */
					for (i=0; i < s_ret; i++) {
						if (isalpha(s_buf[i]))
							s_buf[i] = toupper(s_buf[i]);
					}
					/* 変換したデータをクライアントに送り返す */
					write(s_fd2, s_buf, 1024);
					s_ret = read(s_fd2, s_buf, 1024);
				}
				return 0;
			}
			/* 親プロセスはs_fd2を閉じて接続要求待ちのループに戻る */
			close(s_fd2);
		}

		return 0;
	}else{
		c_fd = init_client();
		// 入力されたデータをソケットに書き込んでサーバーに送り、
		// サーバーが変換して送ってきたデータを読み込む。
		while (fgets(c_buf, 1024, stdin)) {
			write(c_fd, c_buf, 1024);
			c_ret = read(c_fd, c_buf, 1024);
			c_buf[c_ret] = '\0';
			//write(1, buf, ret);
			printf("%s",c_buf);
		}
		close(c_fd);
	}
}
