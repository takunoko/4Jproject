#include "network.h"

int main(void){
	// Serverモードで使う変数
	struct sockaddr_in	s_caddr;
	int s_len;
	int s_ret;
	int s_fd1, s_fd2;
	int s_pid;
	char s_buf[1024];
	int i;

	// ゲームとして使う変数
	int player_num = 0;

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

			/* ユーザーにIDを送信する */
			sprintf( s_buf, "%d", player_num++);
			write(s_fd2, s_buf, 1024);

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
}
