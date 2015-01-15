#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >$B$NBe$o$j(B */

#include "network.h"

int main(void){
	// Server$B%b!<%I$G;H$&JQ?t(B
	struct sockaddr_in	s_caddr;
	int s_len;
	int s_ret;
	int s_fd1, s_fd2;
	int s_pid;
	char s_buf[1024];
	int i;

	// $B%2!<%`$G;HMQ$9$kJQ?t(B
	int user_num = 0;

	/*
	 * accept()$B$K$h$j!"%/%i%$%"%s%H$+$i$N@\B3MW5a$r<u$1IU$1$k!#(B
	 * $B@.8y$9$k$H!"%/%i%$%"%s%H$H@\B3$5$l$?%=%1%C%H$N%G%#%9%/%j%W%?$,(B
	 * fd2$B$KJV$5$l$k!#$3$N(Bfd2$B$rDL$7$FDL?.$,2DG=$H$J$k!#(B
	 */
	s_fd1 = init_server();

	s_len = sizeof(s_caddr);
	for(;;){
		if ((s_fd2 = accept(s_fd1, (struct sockaddr *)&s_caddr, &s_len)) < 0) {
			perror("accept");
			return 1;
		}else{
			// $B@\B3$,$"$k$4$H$K(Buser_num$B$rA}$d$7$F$$$/(B
			user_num++;
			printf("user_num : %d\n", user_num);
		}
		/*
		 *  fork()$B$r;H$C$F:n6H@lMQ$N%W%m%;%9$r:n$k(B
		 *  $B?F%W%m%;%9$O!"<!$N@\B3MW5a$rBT$D$?$a$K%k!<%W$7!"(B
		 *  $B?7$7$/@8@.$5$l$?;R%W%m%;%9$OBgJ8;z$KJQ49$9$k:n6H$@$1$r9T$&(B
		 */
		if ((s_pid = fork()) < 0) {
			perror("fork");
			return 1;
		} else if (s_pid == 0) {
			/* fork()$B$G?7$7$/@8@.$5$l$?%W%m%;%9$O$3$A$i(B */
			/* $B;R%W%m%;%9$KAjEv$9$k(B */
			close(s_fd1);

			/* $B@5>o$K@\B3$7$?>l9g!"%f!<%6!<(BID$B$rJV$9(B */
			sprintf( s_buf, "%d\n", user_num);
			write(s_fd2, s_buf, 1024);

			s_ret = read(s_fd2, s_buf, 1024);
			while (strcmp(s_buf, "quit(J\(Bn") != 0) { // $B;R%W%m%;%9$O$3$NCf$rL58B%k!<%W(B
				/* s_buf$B$NCf$N>.J8;z$rBgJ8;z$KJQ49$9$k(B */
				for (i=0; i < s_ret; i++) {
					if (isalpha(s_buf[i]))
						s_buf[i] = toupper(s_buf[i]);
				}
				/* $BJQ49$7$?%G!<%?$r%/%i%$%"%s%H$KAw$jJV$9(B */
				write(s_fd2, s_buf, 1024);
				s_ret = read(s_fd2, s_buf, 1024);
			}
			return 0;
		}
		/* $B?F%W%m%;%9$O(Bs_fd2$B$rJD$8$F@\B3MW5aBT$A$N%k!<%W$KLa$k(B */
		close(s_fd2);
	}

	return 0;

	return 0;
}
