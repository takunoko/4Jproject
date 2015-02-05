#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >$B$NBe$o$j(B */

#include <err.h> // $B;R%W%m%;%9$N=hM}4XO"(B
#include <errno.h>
#include <sys/wait.h> /* wait() $B;R%W%m%;%9$N=*N;BT$A(B */

#include "game_def.h"
#include "network.h"

typedef struct{
	int u_id;
	int score;
}SCORE;

void init_prog(void);
void multi_wait(void);

int main(void){
	// Server$B%b!<%I$G;H$&JQ?t(B
	struct sockaddr_in	s_caddr;
	int s_len;
	int s_ret;
	int s_fd1;
	int s_fd2[MAX_PLAYER_SIZE];
	int s_pid;
	char s_buf[1024];
	int i;

	// $B%2!<%`$G;HMQ$9$kJQ?t(B
	int user_num = 0;
	int seed;
	SCORE scores[MAX_PLAYER_SIZE];

	// $B%W%m%;%94VDL?.$GMQ$$$k(B
	int fds[2];
	char buf[1024];

	// $B%Q%$%W$N=i4|2=(B
	memset(buf, 0, sizeof(buf));

	// $B%Q%$%W$r:n@.(B
	if (pipe(fds) < 0) {
		perror("pipe()");
		return -1;
	}



	init_prog();
	/*
	 * accept()$B$K$h$j!"%/%i%$%"%s%H$+$i$N@\B3MW5a$r<u$1IU$1$k!#(B
	 * $B@.8y$9$k$H!"%/%i%$%"%s%H$H@\B3$5$l$?%=%1%C%H$N%G%#%9%/%j%W%?$,(B
	 * fd2$B$KJV$5$l$k!#$3$N(Bfd2$B$rDL$7$FDL?.$,2DG=$H$J$k!#(B
	 */
	s_fd1 = init_server();

	s_len = sizeof(s_caddr);
	// for(;;){
	// $B$G$-$l$P!"%f!<%6!<$+$i$NF~NO$G<B9T$r3+;O$7$?$$(B
	// $B$H$j$"$($:!"%f!<%6!<?t$,:G=i$NDj?t$KC#$7$?$i3+;O(B
	while(user_num < MAX_PLAYER_SIZE){
		// accept()$B$GF~NOBT$A$,H/@8$7$F$$$k(B
		// popen(pscmd,"r"); $BFf$N4X?t!!2?$,$7$?$+$C$?$N$+Ff(B
		if ((s_fd2[user_num] = accept(s_fd1, (struct sockaddr *)&s_caddr, &s_len)) < 0) {
			perror("accept");
			return 1;
		}else{
			// $B@\B3$,$"$k$4$H$K(Buser_num$B$rA}$d$7$F$$$/(B
			// user_num++;
			printf("user_num : %d\n", user_num);
		}

		/*
		 *  fork()$B$r;H$C$F:n6H@lMQ$N%W%m%;%9$r:n$k(B
		 *  $B?F%W%m%;%9$O!"<!$N@\B3MW5a$rBT$D$?$a$K%k!<%W$7!"(B
		 *  $B?7$7$/@8@.$5$l$?;R%W%m%;%9$OBgJ8;z$KJQ49$9$k:n6H$@$1$r9T$&(B
		 */
		/*
		if ((s_pid = fork()) < 0) {
			perror("fork");
			return 1;
		} else if (s_pid == 0) {
			// fork()$B$G?7$7$/@8@.$5$l$?%W%m%;%9$O$3$A$i(B
			// $B;R%W%m%;%9$KAjEv$9$k(B
			close(s_fd1);

			// $B@5>o$K@\B3$7$?>l9g!"%f!<%6!<(BID$B$rJV$9(B
			sprintf( s_buf, "%d\n", user_num);
			write(s_fd2, s_buf, 1024);

			s_ret = read(s_fd2, s_buf, 1024);

			// $B;R%W%m%;%9$O$3$NCf$rL58B%k!<%W(B
			while (strcmp(s_buf, "quit(J\(Bn") != 0) {
				// s_buf$B$NCf$N>.J8;z$rBgJ8;z$KJQ49$9$k(B
				for (i=0; i < s_ret; i++) {
					if (isalpha(s_buf[i]))
						s_buf[i] = toupper(s_buf[i]);
				}
				// $BJQ49$7$?%G!<%?$r%/%i%$%"%s%H$KAw$jJV$9(B
				write(s_fd2, s_buf, 1024);
				s_ret = read(s_fd2, s_buf, 1024);
			}

			return -1;
		}
		*/

		// $B@5>o$K@\B3$7$?>l9g!"%f!<%6!<(BID$B$rJV$9(B
		sprintf( s_buf, "%d\n", user_num);
		write(s_fd2[user_num], s_buf, 1024);

		// close(s_fd2[user_num]);
		user_num++;
	}

	// $B%2!<%`3+;O(B

	// seed $BCM$NAw?.(B
	seed = rand();
	// printf("seed : %d\n", seed);
	sprintf(s_buf, "%d", seed);
	for( i=0; i<user_num; i++){
		write(s_fd2[i], s_buf, 1024);
	}


	// $B%f!<%6!<$+$iAw$i$l$F$-$?%9%3%"$N<u$1<h$j(B
	// $B%f!<%6!<?t$@$1%W%m%;%9$r@8@.$9$k(B
	for(i=0; i<user_num; i++){
		// $B3F%f!<%6!<JL$K%W%m%;%9$r@8@.(B
		if ((s_pid = fork()) < 0) {
			perror("fork");
			return 1;
		} else if (s_pid == 0) {
			// $B;R%W%m%;%9(B
			int p_id, p_score;
			read(s_fd2[i], s_buf, 1024);
			sscanf(s_buf,"%d,%d", &p_id ,&p_score);
			printf("process %d score: %d\n", p_id, p_score);

			if(write(fds[1], s_buf, 1024) < 0) {
				perror("write()");
				return -1;
			}

			// $B%Q%$%W$r%/%m!<%:(B
			close(fds[0]); // $BF~NO(B
			close(fds[1]); // $B=PNO(B

			return 0;
		}else{
			// $B?F%W%m%;%9(B
		}
	}

	// $B;R%W%m%;%9$+$i%9%3%"$N<u$1<h$j(B
	for(i=0; i<user_num; i++){
		if(read(fds[0], buf, sizeof(buf)) < 0) {
			perror("read()");
			return -1;
		}
		// $BCM$rFI$_<h$l$F$J$$(B...
		// sscanf( buf, "%d,%d", scores[i].u_id, scores[i].score);
		// printf("id : %d, score : %d", scores[i].u_id, scores[i].score);
	}

	// $B3F%f!<%6!<$KA40wJ,$N%9%3%"$rAw?.$9$k(B
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
				// $B;R%W%m%;%9$,B8:_$7$J$$(B
				break;
			}
			else if(EINTR == errno)
			{
				continue;
			}
			// wait $B$,<:GT$7$?(B
			perror("wait error");
		}
		(void) printf ("parenet: child = %d, status=%d\n", pid, status);
	}
}
