#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/socket.h>

#define MAX 64

int main(void)
{
	int sockfd[2]; /* ���ڱ���Unix���׽��������������� */
	pid_t pid;
	char buf[MAX];
	int n;

	/* ����һ��δ������Unix���׽��֣�������Ϊ��������ʽ��
* sockfd[0]Ϊ���ˣ�sockfd[1]Ϊд��
 */
	if(socketpair(AF_UNIX, SOCK_STREAM, 0, sockfd) == -1){
		perror("fail to create socket");
		exit(1);
	}

	/* ����һ���ӽ��̣����ӽ���ʹ�øոմ�����δ������Unix���׽��ֽ���ͨ�� */
	pid = fork();

	if(pid < 0){ /* �����ӽ��̳��� */
		perror("fail to fork");
		exit(1);
	}else if(pid == 0){ /* �ӽ��� */
		close(sockfd[0]); /* �رն��ˣ��ӽ����򸸽���������� */

		strcpy(buf, "hello parent");
		n = strlen(buf);

		if(write(sockfd[1], buf, n) == -1){ /* �򸸽��̷�����Ϣ */
			perror("fail to write");
exit(1);
		}
		
		printf("the child done\n"); /* �����ʾ��Ϣ��������ֹ���� */
	}else{
		close(sockfd[1]); /* �ر�д�ˣ������̶�ȡ�ӽ��̵���� */
		
		if(read(sockfd[0], buf, MAX) == -1){ /* ��ȡ�ӽ��̷��͸������̵���Ϣ */
			perror("fail to read");
			exit(1);
		}

		n = strlen(buf);
		buf[n] = '\0'; /* ��ӽ������������������Ϣ */

		printf("recive from child : %s\n", buf); /* ����ӽ��̷��͸������̵���Ϣ */
		
		if(wait(NULL) == -1){ /* �����ӽ��̵Ľ���״̬ */
			perror("fail to wait");
			exit(1);
		}

		printf("the parent done\n"); /* ��������̽������е���ʾ��Ϣ */
	}

	return 0;
}
