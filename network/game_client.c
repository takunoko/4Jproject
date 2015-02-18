#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >の代わり */

// client側で使う
#include <netdb.h>

#include "game_def.h"
#include "network.h"
#include "../prottype/race.h"
#include "perce_iwa.h"

int main(void){
	// Clientモードで使う変数
	char	c_buf[1024];
	int		c_ret;
	int		c_fd;

	// ゲームで使用する変数
	int my_id;
	int seed;
	int score;
	// 他ユーザーの情報
	NODE results[MAX_PLAYER_SIZE];

	c_fd = init_client();
	// 入力されたデータをソケットに書き込んでサーバーに送り、
	// サーバーが変換して送ってきたデータを読み込む。

	// サーバーへの接続が成功するとユーザーIDが返される
	read(c_fd, c_buf, 1024);
	my_id = atoi( c_buf);
	printf("my_id : %d\n", my_id);

	// サーバーからのプログラム実行のタイミングを待つ
	// ここで読まれるのは乱数のシード値
	read(c_fd, c_buf, 1024);
	seed = atoi( c_buf);
	srand(seed);

	// ゲームの実行
	score = race(seed);

	// ゲーム終了後、スコアを送信する
	sprintf( c_buf, "%d,%d", my_id, score);
	write( c_fd, c_buf, 1024);


	// 全員分のスコアをサーバーから受け取る
	read(c_fd, c_buf, 1024);

	perce( results, c_buf);
	disp_result( results, MAX_PLAYER_SIZE, my_id);

	close(c_fd);

	return 0;
}
