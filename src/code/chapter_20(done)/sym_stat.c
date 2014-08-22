#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(void)
{
	struct stat buf; /* �洢�ļ�״̬��Ϣ */
	
	if(stat("sl", &buf) == -1){
		perror("fail to stat");
	exit(1);
}
	
	printf("permission : %d\n", buf.st_mode); /* ��ӡ�ļ�Ȩ���� */
	printf("inode number : %d\n", buf.st_ino); /* ��ӡi�ڵ�� */
	printf("device number : %d\n", buf.st_dev); /* ��ӡ�ļ�ϵͳ�豸�� */
	printf("r-device number : %d\n", buf.st_rdev); /* ��ӡӲ���豸�豸�� */
	printf("link : %d\n", buf.st_nlink); /* ��ӡӲ������ */
	printf("uid : %d\n", buf.st_uid); /* ��ӡ�������û�ID */
	printf("gid : %d\n", buf.st_gid); /* ��ӡ��������ID */
	printf("file size : %d\n", buf.st_size); /* ��ӡ�ļ��Ĵ�С */
	printf("access time : %d\n", buf.st_atime); /* ��ӡ���һ�εķ���ʱ��*/
	printf("motify time : %d\n", buf.st_mtime); /* ��ӡ���һ���޸��ļ����ݵ�ʱ�� */
	printf("change time : %d\n", buf.st_ctime); /* ��ӡ���һ���޸��ļ����Ե�ʱ�� */
	printf("buf size : %d\n", buf.st_blksize); /* ��ӡ���ʵĻ�������С */
	printf("block size : %d\n", buf.st_blocks); /* ��ӡ�ļ��������ռ�õ��̿��� */

	if(stat("test.txt", &buf) == -1){
		perror("fail to stat");
	exit(1);
}

	printf("permission : %d\n", buf.st_mode); /* ��ӡ�ļ�Ȩ���� */
	printf("inode number : %d\n", buf.st_ino); /* ��ӡi�ڵ�� */
	printf("device number : %d\n", buf.st_dev); /* ��ӡ�ļ�ϵͳ�豸�� */
	printf("r-device number : %d\n", buf.st_rdev); /* ��ӡӲ���豸�豸�� */
	printf("link : %d\n", buf.st_nlink); /* ��ӡӲ������ */
	printf("uid : %d\n", buf.st_uid); /* ��ӡ�������û�ID */
	printf("gid : %d\n", buf.st_gid); /* ��ӡ��������ID */
	printf("file size : %d\n", buf.st_size); /* ��ӡ�ļ��Ĵ�С */
	printf("access time : %d\n", buf.st_atime); /* ��ӡ���һ�εķ���ʱ��*/
	printf("motify time : %d\n", buf.st_mtime); /* ��ӡ���һ���޸��ļ����ݵ�ʱ�� */
	printf("change time : %d\n", buf.st_ctime); /* ��ӡ���һ���޸��ļ����Ե�ʱ�� */
	printf("buf size : %d\n", buf.st_blksize); /* ��ӡ���ʵĻ�������С */
	printf("block size : %d\n", buf.st_blocks); /* ��ӡ�ļ��������ռ�õ��̿��� */
	
return 0;
}
