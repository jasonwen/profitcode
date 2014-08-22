#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

/* ����ʹ�õĽṹ�塣������������Ա���� */
struct a{
	int b;
	int c;	
}r3; /* ����ȫ�ֱ���r3 */

/* ��һ���߳�ʹ�þֲ����������˳���Ϣ�ṹ */
void * tfn1(void * arg)
{
	struct a r1;	
	printf("the first one\n "); /* �����ʾ��Ϣ */
	
	r1.b = 10; /* �����˳���Ϣ�ṹ */
	r1.c = 11;
	
	return (void *)(&r1); /* �����˳���Ϣ�ṹ���׵�ַ */
}

/* �ڶ�������ʹ�ö�̬�����ڴ�ķ�ʽ�洢�˳���Ϣ�ṹ */
void * tfn2(void * arg)
{
	struct a * r2; 
	
	printf("the second one\n ");  /* �����ʾ��Ϣ */
	
	r2 =(struct a *) malloc(sizeof(struct a)); /* ʹ�ö�̬������ڴ� */
	
	printf("structure at %x\n", r2);
	
	r2->b = 10; /* �����˳���Ϣ */
	r2->c = 11;
	
	return (void *)r2; /* �����˳��ṹ���׵�ַ */
}

/* ����������ʹ��ȫ�ֱ����洢�˳���Ϣ�ṹ */
void * tfn3(void * arg)
{
	printf("the third one\n:"); /* �����ʾ��Ϣ */
	
	r3.b = 10; /* �����˳���Ϣ�ṹ */
	r3.c = 11;
	
	return (void *)(&r3); /*�����˳��ṹ���׵�ַ*/
}

/* ���ĸ�����ʹ��main�����еľֲ������洢�˳���Ϣ�ṹ */
void * tfn4(void * arg)
{
	struct a *r4 = (struct a *)arg;

	printf("the fourth one\n");  /* �����ʾ��Ϣ */
	
	r4->b = 10; /* �����˳���Ϣ�ṹ */
	r4->c = 11;
	
	return (void *)(&r4); /*�����˳��ṹ���׵�ַ*/
}

int main(void)
{
 	pthread_t tid1, tid2, tid3, tid4;
 	void * res;
 	int err;
 		
	/* ִ�е�һ���߳� */
 	err = pthread_create(&tid1, NULL, tfn1, NULL); /* �����߳� */
	if(err != 0){
		printf("can��t create thread %s\n", strerror(err));
		exit(1);	
	}
	
	err = pthread_join(tid1, &res); /* �õ��̵߳Ľ�����Ϣ */
	if(err != 0){
		printf("can��t join thread %s\n", strerror(err));
		exit(1);	
	}
	printf("1st result: %d, %d\n", ((struct a *)res)->b, ((struct a *)res)->c); /* ��ӡ�˳���Ϣ */
	
	/* ִ�еڶ����߳� */
	err = pthread_create(&tid2, NULL, tfn2, NULL);
	if(err != 0){
		printf("can��t create thread %s\n", strerror(err));
		exit(1);	
	}
	
	err = pthread_join(tid2, &res); /* �õ��̵߳Ľ�����Ϣ */
	if(err != 0){
		printf("can��t join thread %s\n", strerror(err));
		exit(1);	
	}
	printf("2nd result: %d, %d\n", ((struct a *)res)->b, ((struct a *)res)->c); /* ���ִ�н�� */
	free(res); /* �ͷ�res��ָ����ڴ����� */

	/* ִ�е������߳� */
	err = pthread_create(&tid3, NULL, tfn3, NULL);
	if(err != 0){
		printf("can��t create thread %s\n", strerror(err));
		exit(1);	
	}
	
	err = pthread_join(tid3, &res); /* �õ��̵߳Ľ�����Ϣ */
	if(err != 0){
		printf("can��t join thread %s\n", strerror(err));
		exit(1);	
	}
	printf("3rd result: %d, %d\n", ((struct a *)res)->b, ((struct a *)res)->c); /* ���ִ�н�� */

	/* ִ�е��ĸ��߳� */
	err = pthread_create(&tid4, NULL, tfn2, NULL);
	if(err != 0){
		printf("can��t create thread %s\n", strerror(err));
		exit(1);	
	}
	
	err = pthread_join(tid4, &res); /* �õ��̵߳Ľ�����Ϣ */
	if(err != 0){
		printf("can��t join thread %s\n", strerror(err));
		exit(1);	
	}
	printf("4th result: %d, %d\n", ((struct a *)res)->b, ((struct a *)res)->c); /* ���ִ�н�� */
	
 	return 0;
}
