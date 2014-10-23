/*
 * mserver2.c
 *   �N���C�A���g����̐ڑ��v�����󂯕t����T�[�o�[�v���O�����B
 *   �啶���ւ̕ϊ���fork()�Ő������ꂽ�q�v���Z�X���s���B
 *   STREAM�^�̃\�P�b�g���g���B
 */

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>  /* #include < sys/un.h >�̑��� */

#define PORT 8765

main()
{
    int    i;
    int    fd1, fd2;
    struct sockaddr_in    saddr;
    struct sockaddr_in    caddr;
    int    len;
    int    ret;
    char   buf[1024];
    int    pid;
    int    msglen;

    /*
     * �\�P�b�g�����B���̃\�P�b�g��UNIX�h���C���ŁA�X�g���[���^�\�P�b�g�B
     */
    if ((fd1 = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
	perror("socket");
	return 1;
    }

    /* 
     * saddr�̒��g��0�ɂ��Ă����Ȃ��ƁAbind()�ŃG���[���N���邱�Ƃ�����
     */
    bzero((char *)&saddr, sizeof(saddr));

    /*
     * �\�P�b�g�̖��O�����Ă���
     */
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = INADDR_ANY;
    saddr.sin_port = htons(PORT);

    /*
     * �\�P�b�g�ɃA�h���X���o�C���h����B
     */
    if (bind(fd1, (struct sockaddr *)&saddr, sizeof(saddr)) < 0){
	perror("bind");
	return 1;
    }
    
    /*
     * listen���\�P�b�g�ɑ΂��Ĕ��s����
     */
    if (listen(fd1, 1) < 0) {
	perror("listen");
	return 1;
    }

    len = sizeof(caddr);
    /*
     * accept()�ɂ��A�N���C�A���g����̐ڑ��v�����󂯕t����B
     * ��������ƁA�N���C�A���g�Ɛڑ����ꂽ�\�P�b�g�̃f�B�X�N���v�^��
     * fd2�ɕԂ����B����fd2��ʂ��ĒʐM���\�ƂȂ�B
     */
    for(;;){
	if ((fd2 = accept(fd1, (struct sockaddr *)&caddr, &len)) < 0) {
	    perror("accept");
	    return 1;
	}
	/* 
	 *  fork()���g���č�Ɛ�p�̃v���Z�X�����
	 *  �e�v���Z�X�́A���̐ڑ��v����҂��߂Ƀ��[�v���A
         *  �V�����������ꂽ�q�v���Z�X�͑啶���ɕϊ������Ƃ������s��
	 */  
	if ((pid = fork()) < 0) {
	    perror("fork");
	    return 1;
	} else if (pid == 0) {
	    /* fork()�ŐV�����������ꂽ�v���Z�X�͂����� */
	    close(fd1);
	    ret = read(fd2, buf, 1024);
	    while (strcmp(buf, "quit\n") != 0) {
		/* buf�̒��̏�������啶���ɕϊ����� */
		for (i=0; i < ret; i++) {
		    if (isalpha(buf[i]))
			buf[i] = toupper(buf[i]);
		}   
		/* �ϊ������f�[�^���N���C�A���g�ɑ���Ԃ� */
		write(fd2, buf, 1024);
		ret = read(fd2, buf, 1024);
	    }
	    return 0;
	}
	/* �e�v���Z�X��fd2����Đڑ��v���҂��̃��[�v�ɖ߂� */
	close(fd2);
    }
}


