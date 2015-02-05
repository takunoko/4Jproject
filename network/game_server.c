#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >の代わり */

#include <err.h> // 子プロセスの処理関連
#include <errno.h>
#include <sys/wait.h> /* wait() 子プロセスの終了待ち */

#include "game_def.h"
#include "network.h"

typedef struct{
	int u_id;
	int score;
}SCORE;

void init_prog(void);
void multi_wait(void);

int main(void){
	// Serverモードで使う変数
	struct sockaddr_in	s_caddr;
	int s_len;
	int s_ret;
	int s_fd1;
	int s_fd2[MAX_PLAYER_SIZE];
	int s_pid;
	char s_buf[1024];
	int i;

	// ゲームで使用する変数
	int user_num = 0;
	int seed;
	SCORE scores[MAX_PLAYER_SIZE];

	// プロセス間通信で用いる
	int fds[2];
	char buf[1024];

	// パイプの初期化
	memset(buf, 0, sizeof(buf));

	// パイプを作成
	if (pipe(fds) < 0) {
		perror("pipe()");
		return -1;
	}



	init_prog();
	/*
	 * accept()により、クライアントからの接続要求を受け付ける。
	 * 成功すると、クライアントと接続されたソケットのディスクリプタが
	 * fd2に返される。このfd2を通して通信が可能となる。
	 */
	s_fd1 = init_server();

	s_len = sizeof(s_caddr);
	// for(;;){
	// できれば、ユーザーからの入力で実行を開始したい
	// とりあえず、ユーザー数が最初の定数に達したら開始
	while(user_num < MAX_PLAYER_SIZE){
		// accept()で入力待ちが発生している
		// popen(pscmd,"r"); 謎の関数　何がしたかったのか謎
		if ((s_fd2[user_num] = accept(s_fd1, (struct sockaddr *)&s_caddr, &s_len)) < 0) {
			perror("accept");
			return 1;
		}else{
			// 接続があるごとにuser_numを増やしていく
			// user_num++;
			printf("user_num : %d\n", user_num);
		}

		/*
		 *  fork()を使って作業専用のプロセスを作る
		 *  親プロセスは、次の接続要求を待つためにループし、
		 *  新しく生成された子プロセスは大文字に変換する作業だけを行う
		 */
		/*
		if ((s_pid = fork()) < 0) {
			perror("fork");
			return 1;
		} else if (s_pid == 0) {
			// fork()で新しく生成されたプロセスはこちら
			// 子プロセスに相当する
			close(s_fd1);

			// 正常に接続した場合、ユーザーIDを返す
			sprintf( s_buf, "%d\n", user_num);
			write(s_fd2, s_buf, 1024);

			s_ret = read(s_fd2, s_buf, 1024);

			// 子プロセスはこの中を無限ループ
			while (strcmp(s_buf, "quit\n") != 0) {
				// s_bufの中の小文字を大文字に変換する
				for (i=0; i < s_ret; i++) {
					if (isalpha(s_buf[i]))
						s_buf[i] = toupper(s_buf[i]);
				}
				// 変換したデータをクライアントに送り返す
				write(s_fd2, s_buf, 1024);
				s_ret = read(s_fd2, s_buf, 1024);
			}

			return -1;
		}
		*/

		// 正常に接続した場合、ユーザーIDを返す
		sprintf( s_buf, "%d\n", user_num);
		write(s_fd2[user_num], s_buf, 1024);

		// close(s_fd2[user_num]);
		user_num++;
	}

	// ゲーム開始

	// seed 値の送信
	seed = rand();
	// printf("seed : %d\n", seed);
	sprintf(s_buf, "%d", seed);
	for( i=0; i<user_num; i++){
		write(s_fd2[i], s_buf, 1024);
	}


	// ユーザーから送られてきたスコアの受け取り
	// ユーザー数だけプロセスを生成する
	for(i=0; i<user_num; i++){
		// 各ユーザー別にプロセスを生成
		if ((s_pid = fork()) < 0) {
			perror("fork");
			return 1;
		} else if (s_pid == 0) {
			// 子プロセス
			int p_id, p_score;
			read(s_fd2[i], s_buf, 1024);
			sscanf(s_buf,"%d,%d", &p_id ,&p_score);
			printf("process %d score: %d\n", p_id, p_score);

			if(write(fds[1], s_buf, 1024) < 0) {
				perror("write()");
				return -1;
			}

			// パイプをクローズ
			close(fds[0]); // 入力
			close(fds[1]); // 出力

			return 0;
		}else{
			// 親プロセス
		}
	}

	// 子プロセスからスコアの受け取り
	for(i=0; i<user_num; i++){
		if(read(fds[0], buf, sizeof(buf)) < 0) {
			perror("read()");
			return -1;
		}
		// 値を読み取れてない...
		// sscanf( buf, "%d,%d", scores[i].u_id, scores[i].score);
		// printf("id : %d, score : %d", scores[i].u_id, scores[i].score);
	}

	// 各ユーザーに全員分のスコアを送信する
	for(i=0; i<user_num; i++){

	}

	printf("end\n");

	return 0;
}

void init_prog(void){
	srand((unsigned)time(NULL));
}

void multi_wait (){
	while(1){
		pid_t	pid;
		int	status = 0;

		pid = wait(&status);

		if (pid == -1)
		{
			if (ECHILD == errno)
			{
				// 子プロセスが存在しない
				break;
			}
			else if(EINTR == errno)
			{
				continue;
			}
			// wait が失敗した
			perror("wait error");
		}
		(void) printf ("parenet: child = %d, status=%d\n", pid, status);
	}
}
