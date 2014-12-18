#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <sys/time.h>   // selectシステムコール
#include <unistd.h>

#define PORT 8765       // サーバーが使うポート番号
#define SOCK_MAX 5      // 最大ソケット数をここで決めた (最大32)
#define UNUSED (-1)

char *Modification(char *str, int length);

int main()
{
  int s[SOCK_MAX + 1]; // array of socket descriptors
  int max = 0;         // max num of used socket
  int n = 0;
  int len;
  fd_set readfds;
  int clilen;               /* client length */
  struct sockaddr_in saddr; /* サーバ側(自分)のアドレス情報 */
  struct sockaddr_in caddr; /* クライアント側のアドレス情報を入れるところ */
  char str[1024];           /* string buffer */
  int i, j;                 /* loop counter */
  int msglen;
  
  // ソケットを作る。
  // このソケットはINETドメインでストリーム型(コネクション型) 。
  if ((s[0] = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    return 1;
  }
  
  // saddrの中身を0にしておかないと、bind()でエラーが起こることがある
  bzero((char *)&saddr, sizeof(saddr));
  
  // ソケットに名前をつける bind()
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = INADDR_ANY;
  saddr.sin_port = htons(PORT); // 定数PORTは#defineしたもの
  
  if ((bind(s[0], (struct sockaddr *)&saddr, sizeof(saddr))) == -1) {
    perror("bind");
    return 1;
  }
  
  // 接続されるのを待つ listen()
  // 第2引数の値を大きくする
  if ((listen(s[0], SOCK_MAX)) == -1) {
    perror("listen");
    return 1;
  } 
  max = 1;   // s[0] is ready
  
  // メインループ
  while (1) {
    FD_ZERO(&readfds);    // fdsの初期化
    printf("max: %d\n", max);

    // すでにクライアントと接続されているソケットのビットを
    // セットしてselect()の検査対象にする。
    for (i = 0; i < max; i++) {
      if (s[i] != UNUSED) {
	FD_SET(s[i], &readfds);
      }
    }
    // メッセージが到着しているソケットがないか調べる
    if ((n = select(FD_SETSIZE, &readfds, NULL, NULL, NULL)) == -1) {
      perror("select");
      return 1;
    }
    printf("select returns: %d\n", n);
    // 1～maxのソケットに届くのは、すでに接続されているクライアントからの
    // メッセージである。
    // もしメッセージがあれば、接続されているすべてのクライアントに送る。
    for (i = 1; i < max; i++) {
      if (s[i] != UNUSED) {
	if (FD_ISSET(s[i], &readfds)) {
	  // s[i]のビットが立っていれば、s[i]にメッセージが到着している
	  printf("s[%d] ready for reading\n", i);
	  if ((msglen = read(s[i], str, sizeof(str))) == -1) {
	    // 受信失敗
	    perror("read");
	  } else if (msglen != 0) {
	    // メッセージの受信に成功
	    printf("client[%d]: %s", i, str);
	    Modification(str,msglen);   // 作業
	    // 接続されているクライアントすべてにメッセージを送る
	    for (j = 1; j < max; j++) {
	      if (s[j] != UNUSED) {
		write(s[j], str, strlen(str));
	      }
	    }
	  } else {
	    printf("client[%d]: connection closed.\n", i);
	    close(s[i]);
	    s[i] = UNUSED;
	  }
	}
      }
    }	
    // 新たな接続要求があった場合は、s[0]のビットが立つ。
    // 以下では新たな接続の受け付けを行う。
    if (FD_ISSET(s[0], &readfds) != 0) {
      printf("Accept New one.\n");
      // 接続を確立する accept()
      len = sizeof(caddr);
      s[max] = accept(s[0], (struct sockaddr *)&caddr, &len);
      printf("%d = accept()\n", s[max]);
      if (s[max] == -1) {
	perror(NULL);
	return 1;
      }
      if (max < SOCK_MAX) {
	printf("client accepted(%d).\n", max);
	max++;
      } else {
	printf("refuse connection.\n");
	strcpy(str, "Server is too busy.\n");
	write(s[max], str, strlen(str));
	close(s[max]);
      }
    }
  }
}

// 大文字に変換する
char *Modification(char *str, int length) {
  int i;
  for (i = 0; i < length; i++) {
    if (isalpha(str[i])) {
      str[i] = toupper(str[i]);
    }
  }
  
  return str;
}
