#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_ITEM 3 /* ÿ�����ȡ�������� */

typedef struct job * Job;

/* ������ṹ */
struct job{
	pthread_t tid; /* �߳�ID */
	Job next; /* ��һ�������� */
	int val; /* ���ֵ */
};

pthread_mutex_t q_lock = PTHREAD_MUTEX_INITIALIZER; /* ȫ�ֱ����� */

int insert(Job *head, int val, pthread_t tid)
{
	Job p, q;

	p = *head; /* ͷָ�� */

	if(p != NULL){ /* �жϿ��������� */
		while(p->next != NULL){
			p = p->next;	
		}	
	}	

	q = (struct job *)malloc(sizeof(struct job)); /* Ϊ�������ڴ�ռ� */
	if(q == NULL){
		perror("fail to malloc");
		return -1;
	}
			
	q->next = NULL;
	q->val = val;
	q->tid = tid; /* ���ý��������ߣ��߳�1 */
	p->next = q; /* ���������������� */
	
	if(p == NULL){ /* ��������ͷָ�� */
		*head = q;
		return 0;	
	}
	
	p->next = q; /* ���뵽������ */

	return 0;
}

void get_job(Job head, Job task, int *count)
{
	struct job *p, *q;
	pthread_t tid;

	q = head; /* �������������ͷ */
	p = q->next; /* ָ��p��Ϊq�ĺ�̣�����ָ�빲ͬǰ�� */
	
	tid = pthread_self();

	while(p != NULL){ /* ���������ж�ÿ�������� */
		if(tid == p->tid){ /* �ҵ����ڵ�ǰ�̵߳������� */
			q->next = p->next;
			p->next = task; /* ���ý���ԭʼ�����������ժ�� */
			task = p; /* ���뵽�µĵ�ǰ�̵߳����������ȥ */
			p = q->next;
			*count++; /* ��ȡ�����ǵ��� */
		}else{
			q = p;
			p = p->next;
		}
	}
}

int free_job(Job head)
{
	Job p, q;

	for(p = head; p != NULL; p = p->next){ /* �߳��˳�ʱ�ͷ����е������� */
		q = p;
         p = p->next;
			free(q);
	}

	return 0;
}

void print(Job head)
{
	Job p;
	
	for(p = head; p != NULL; p = p->next) /* ���ȡ�õ������б� */
		printf("thread %u: %d\n", p->tid, p->val);
}

void * tfn7(void * arg)
{
	int count; /* ÿ��ȡ���������� */
	struct job * task = NULL; /* ���ڵ�ǰ�̵߳�������Ķ���ͷ */
	pthread_t tid;

	tid = pthread_self(); /* �õ���ǰ�߳�ID�����ݴ��߳�ID�ж������Ƿ�����ڵ�ǰ�߳� */
	
	count = 0;
	while(count < MAX_ITEM)
		if(pthread_mutex_trylock(&q_lock) == 0){ /* �����м��� */
			get_job((Job) arg, task, &count);
			pthread_mutex_unlock(&q_lock); /* ��������������ͷ��� */
		}

	print((Job) arg);

	if(free_job(task) == -1)
		exit(1);

	return (void *)0;
}

int main(void)
{
	struct job * item; /* ���������һ����ͷ�������� */
	pthread_t tid1, tid2;
	int i; 
	int err;
		
	item = (struct job *)malloc(sizeof(struct job)); /* ����ͷ��㣬�ý�㲻�洢��Ч��Ϣ */
	item->next = NULL;
	item->val = 0;
	item->tid = -1;
	
	/* ���������̣߳��������̻߳�����Լ����߳�IDȡ�߲�ͬ�������� */
	if((err = pthread_create(&tid1, NULL, tfn7, item)) != 0){ /* ������һ���̣߳����������ͷ��Ϊ�߳��庯������ */
		printf("fail to create thread %s\n", strerror(err));
		exit(0);	
	}
	if((err = pthread_create(&tid2, NULL, tfn7, item)) != 0){ /* �����ڶ����̣߳����������ͷ��Ϊ�߳��庯������*/
		printf("fail to create thread %s\n", strerror(err));
		exit(0);	
	}

	printf("===the 1st put===\n"); /* ��һ��ִ�У������߳̽����������õ���������� */

	pthread_mutex_lock(&q_lock); /*��ס������� */
	for(i = 0; i < 2; i++){ /* ��ִ�����Σ�ÿ�η���������㣬һ�������߳�1��һ�������߳�2 */
		if(insert(&item, i, tid1) == -1)
			exit(1);
		if(insert(&item, i + 1, tid2) == -1)
			exit(1);
	}
		
	if(insert(&item, 10, tid1) == -1)
		exit(1);
		
	pthread_mutex_unlock(&q_lock); /* �ͷ�������ǰ�������������������㣬3�������߳�1��2�������߳�2 */
	 
	sleep(5); 
	/* ���ߣ���֤�߳̿���ȡ�������㣬�����ﲻ��ʹ��pthread_join������
	* ��Ϊ������ֻ��������������߳�2��δȡ����������߳��ǲ����˳��ġ�
	* ����pthread_join�����ᵼ������ 
	*/
	
	printf("===the 2nd put===\n"); /* �ڶ������룬Ŀǰ�������Ѿ�û���������� */
	
	pthread_mutex_lock(&q_lock); /* �ٴ���ס���� */
	if(insert(&item, 9, tid2) == -1)
		exit(1);
	pthread_mutex_unlock(&q_lock); /* �ͷ��� */
	
	/* ���ʱ�����ʹ��pthred_join������ */
	err = pthread_join(tid1, NULL); /* �õ��߳�1���˳���Ϣ */
	if(err != 0){
		printf("can��t join thread %s\n", strerror(err));
		exit(1);	
	}
	err = pthread_join(tid2, NULL); /* �õ��߳�2���˳���Ϣ */
	if(err != 0){
		printf("can��t join thread %s\n", strerror(err));
		exit(1);	
	}
	
	printf("main thread done\n"); /* �����ʾ��Ϣ */
	if(item->next == NULL) /* ���������û���������ˣ��������ʾ��Ϣ�� */
		printf("No job in the queue\n");	
	free(item); /* �ͷ�ͷ��� */

	return 0;
}
