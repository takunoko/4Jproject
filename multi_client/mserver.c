#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h> 
#include <sys/time.h>   // select�V�X�e���R�[��
#include <unistd.h>

#define PORT 8765       // �T�[�o�[���g���|�[�g�ԍ�
#define SOCK_MAX 5      // �ő�\�P�b�g���������Ō��߂� (�ő�32)
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
  struct sockaddr_in saddr; /* �T�[�o��(����)�̃A�h���X��� */
  struct sockaddr_in caddr; /* �N���C�A���g���̃A�h���X��������Ƃ��� */
  char str[1024];           /* string buffer */
  int i, j;                 /* loop counter */
  int msglen;
  
  // �\�P�b�g�����B
  // ���̃\�P�b�g��INET�h���C���ŃX�g���[���^(�R�l�N�V�����^) �B
  if ((s[0] = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("socket");
    return 1;
  }
  
  // saddr�̒��g��0�ɂ��Ă����Ȃ��ƁAbind()�ŃG���[���N���邱�Ƃ�����
  bzero((char *)&saddr, sizeof(saddr));
  
  // �\�P�b�g�ɖ��O������ bind()
  saddr.sin_family = AF_INET;
  saddr.sin_addr.s_addr = INADDR_ANY;
  saddr.sin_port = htons(PORT); // �萔PORT��#define��������
  
  if ((bind(s[0], (struct sockaddr *)&saddr, sizeof(saddr))) == -1) {
    perror("bind");
    return 1;
  }
  
  // �ڑ������̂�҂� listen()
  // ��2�����̒l��傫������
  if ((listen(s[0], SOCK_MAX)) == -1) {
    perror("listen");
    return 1;
  } 
  max = 1;   // s[0] is ready
  
  // ���C�����[�v
  while (1) {
    FD_ZERO(&readfds);    // fds�̏�����
    printf("max: %d\n", max);

    // ���łɃN���C�A���g�Ɛڑ�����Ă���\�P�b�g�̃r�b�g��
    // �Z�b�g����select()�̌����Ώۂɂ���B
    for (i = 0; i < max; i++) {
      if (s[i] != UNUSED) {
	FD_SET(s[i], &readfds);
      }
    }
    // ���b�Z�[�W���������Ă���\�P�b�g���Ȃ������ׂ�
    if ((n = select(FD_SETSIZE, &readfds, NULL, NULL, NULL)) == -1) {
      perror("select");
      return 1;
    }
    printf("select returns: %d\n", n);
    // 1�`max�̃\�P�b�g�ɓ͂��̂́A���łɐڑ�����Ă���N���C�A���g�����
    // ���b�Z�[�W�ł���B
    // �������b�Z�[�W������΁A�ڑ�����Ă��邷�ׂẴN���C�A���g�ɑ���B
    for (i = 1; i < max; i++) {
      if (s[i] != UNUSED) {
	if (FD_ISSET(s[i], &readfds)) {
	  // s[i]�̃r�b�g�������Ă���΁As[i]�Ƀ��b�Z�[�W���������Ă���
	  printf("s[%d] ready for reading\n", i);
	  if ((msglen = read(s[i], str, sizeof(str))) == -1) {
	    // ��M���s
	    perror("read");
	  } else if (msglen != 0) {
	    // ���b�Z�[�W�̎�M�ɐ���
	    printf("client[%d]: %s", i, str);
	    Modification(str,msglen);   // ���
	    // �ڑ�����Ă���N���C�A���g���ׂĂɃ��b�Z�[�W�𑗂�
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
    // �V���Ȑڑ��v�����������ꍇ�́As[0]�̃r�b�g�����B
    // �ȉ��ł͐V���Ȑڑ��̎󂯕t�����s���B
    if (FD_ISSET(s[0], &readfds) != 0) {
      printf("Accept New one.\n");
      // �ڑ����m������ accept()
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

// �啶���ɕϊ�����
char *Modification(char *str, int length) {
  int i;
  for (i = 0; i < length; i++) {
    if (isalpha(str[i])) {
      str[i] = toupper(str[i]);
    }
  }
  
  return str;
}
