#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >の代わり */

// client側で使う
#include <netdb.h>

#include "network.h"

int main(void){
	// Clientモードで使う変数
	char	c_buf[1024];
	int		c_ret;
	int		c_fd;

	// ゲームで使用する変数
	int my_id;

	c_fd = init_client();
	// 入力されたデータをソケットに書き込んでサーバーに送り、
	// サーバーが変換して送ってきたデータを読み込む。

	// サーバーへの接続が成功するとユーザーIDが返される
	read(c_fd, c_buf, 1024);
	my_id = atoi( c_buf);
	printf("my_id : %d\n", my_id);

	// while (fgets(c_buf, 1024, stdin)) {
	// 	write(c_fd, c_buf, 1024);
	// 	c_ret = read(c_fd, c_buf, 1024);
	// 	c_buf[c_ret] = '\0';
	// 	printf("%s",c_buf);
	// }

	// サーバーからのプログラム実行のタイミングを待つ
	// ここで読まれるのは乱数のシード値
	read(c_fd, c_buf, 1024);
	srand(atoi( c_buf));

	printf("init_game\n");

	// ゲームスタートが呼ばれる
	read(c_fd, c_buf, 1024);
	printf("str : %s\n", c_buf);


	close(c_fd);

	return 0;
}
