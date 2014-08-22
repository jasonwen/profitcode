#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <errno.h>
#include "iolib.h" /* �û��Լ���I/O������ */

#define MAX_LINE 80
int port = 8000; /*  */

/* �����������ڽ���д�ַ�ת��ΪСд�ַ�������Ϊ��Ҫת�����ַ��� */
void my_fun(char * p)
{
	if(p == NULL) /* �մ� */
		return;

	for (; *p != '\0'; p++)
		if(*p >= 'A'&& *p <= 'Z') /* �ж��ַ�������ת����Ҳ����ʹ�ÿ⺯�� */
			*p = *p -'A'+ 'a';
}

int main(void)
{
     struct sockaddr_in sin;
     struct sockaddr_in cin;
     int lfd;
     int cfd;
     int sfd;
int rdy;
int client[FD_SETSIZE]; /* �ͻ������ӵ��׽������������� */
     int maxi;
     int maxfd; /* ��������� */
     fd_set rset;
     fd_set allset;
     socklen_t addr_len; /* ��ַ�ṹ�ĳ��� */
     char buf[MAX_LINE];
     char str[INET_ADDRSTRLEN];
     int i;
     int n;
int len;
int opt = 1; /* �׽���ѡ�� */
	char addr_p[18];

     bzero(&sin, sizeof(sin)); /* ����ַ�ṹ */
     sin.sin_family = AF_INET;
     sin.sin_addr.s_addr = INADDR_ANY;
     sin.sin_port = htons(port);

	/* ����һ���������ӵ��׽��� */
     lfd = socket(AF_INET, SOCK_STREAM, 0);
     if (lfd == -1) {
          perror("call to socket");
          exit(1);
     }
     
	/* �����׽���ѡ�ʹ��Ĭ��ѡ�� */
setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

/* ���׽��ֵ���ַ�ṹ */
     n = bind(lfd, (struct sockaddr *) &sin, sizeof(sin));
     if (n == -1) {
          perror("call to bind");
          exit(1);
}

/* ��ʼ������������ */
     n = listen(lfd, 20);
     if (n == -1) {
          perror("call to listen"), exit(1);
}

     printf("Accepting connections ...\n"); 

     maxfd = lfd; /* ������ļ������������г�ʼ�� */
maxi = -1;

     for (i = 0; i < FD_SETSIZE; i++)  /* ��ʼ���ͻ����������������� */
          client[i] = -1;        

     FD_ZERO(&allset); /* ����ļ����������� */
     FD_SET(lfd, &allset); /* ���������������ڼ����� */

	/* ��ʼ�������������ѭ�� */
     while(1){
         rset = allset;

		/* �õ���ǰ���Զ����ļ��������� */
         rdy = select(maxfd + 1, &rset, NULL, NULL, NULL);

         if (FD_ISSET(lfd, &rset)){
addr_len = sizeof(cin);

/* ����һ������������ */
              cfd = accept(lfd, (struct sockaddr *) &cin, &addr_len);
			if(cfd == -1){
				perror("fail to accept");
				exit(1);
			}

/* ����һ�����е�λ�� */
              for (i = 0; i < FD_SETSIZE; i++)
                   if (client[i] < 0){
                        client[i] = cfd; /* ������ÿͻ��˵������׽������õ���λ�� */
                        break;
}
			
			/* ̫��Ŀͻ������ӣ��������ܾ����ӣ�����ѭ�� */
			if (i == FD_SETSIZE){
                   printf("too many clients");
                   exit(1);
}

FD_SET(cfd, &allset); /* �������Ӽ��� */

if (cfd > maxfd) /* �µ����������� */
                   maxfd = cfd; 
              if (i > maxi)
                   maxi = i;
              if (--rdy <= 0) /* ����һ������������ */
                   continue;
          }

		for (i = 0; i <= maxi; i++){ /* ��ÿһ������������������ */
               if ((sfd = client[i]) < 0)
                    continue;
               
if (FD_ISSET(sfd, &rset)){
	
                   n = my_read(sfd, buf, MAX_LINE); /* ��ȡ���� */
                   if (n == 0){
                        printf("the other side has been closed.\n");
                        fflush(stdout); /* ˢ�µ�����ն� */
                        close(sfd);
					
                        FD_CLR(sfd, &allset); /* ����������������� */
                        client[i] = -1;
                   }else{
					/* ���ͻ��˵�ַת��Ϊ�ַ��� */
                       	inet_ntop(AF_INET, &cin.sin_addr, addr_p, sizeof(addr_p));    
     
					/* ��ӡ�ͻ��˵�ַ�Ͷ˿ں� */
					printf("client IP is %s, port is %d\n", addr_p, ntohs(sin.sin_port));
printf("content is : %s\n", buf); /* ��ӡ�ͻ��˷��͹������ַ��� */

					my_fun(buf); /* ���ô�Сдת������ */
					
                       n = my_write(sfd, buf, len + 1);
					if(n == -1) /* д�������� */
						exit(1);
}

                    if (--rdy <= 0)
                         break;      /* ���û�п��Զ����׽������˳�ѭ�� */
               }
          }
}

close(lfd); /* �ر������׽��� */

return 0;
}
