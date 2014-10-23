#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 8765

main(int argc, char *argv[])
{
    struct sockaddr_in addr;
    struct hostent *hp;
    int    fd;
    int    len;
    char   buf[1024];
    int    ret;



    if (argc != 2){
	printf("Usage: iclient SERVER_NAME\n");
	return 1;
    }

    // �\�P�b�g�����B���̃\�P�b�g��INET�h���C���ŁA�X�g���[���^�\�P�b�g�B
    if ((fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return 1;
    }

    // addr�̒��g��0�ɂ��Ă����Ȃ��ƁAbind()�ŃG���[���N���邱�Ƃ�����
    bzero((char *)&addr, sizeof(addr));

    // �\�P�b�g�̖��O�����Ă���
    if ((hp = gethostbyname(argv[1])) == NULL) {
	perror("No such host");
	return 1;
    }

    bcopy(hp->h_addr, &addr.sin_addr, hp->h_length);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(PORT);

    // �T�[�o�[�Ƃ̐ڑ������݂�B���ꂪ�������邽�߂ɂ́A�T�[�o�[�����ł�
    // ���̃A�h���X��bind()���āAlisten()�𔭍s���Ă��Ȃ���΂Ȃ�Ȃ��B
    if (connect(fd, (struct sockaddr *)&addr, sizeof(addr)) < 0){
        perror("connect");
        return 1;
    }

    // ���͂��ꂽ�f�[�^���\�P�b�g�ɏ�������ŃT�[�o�[�ɑ���A
    // �T�[�o�[���ϊ����đ����Ă����f�[�^��ǂݍ��ށB
    while (fgets(buf, 1024, stdin)) {
        write(fd, buf, 1024);
        ret = read(fd, buf, 1024);
	buf[ret] = '\0';
        //write(1, buf, ret);
        printf("%s",buf);
    }
    close(fd);
    return 0;
}



