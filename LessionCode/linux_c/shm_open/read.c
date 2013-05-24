#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

/*
int shm_open(const char *name, int oflag, mode_t mode);
//�������һ�������ڴ�,�ɹ�����һ���������ļ������������󷵻�-1��
1.name:�����ڴ��������֣�
2.��־λ��open�ı�־һ��
3.Ȩ��λ
int shm_unlink(const char *name);

����ʱҪ�ӿ��ļ�-lrt
*/

#define SHMNAME "shm_ram"
#define OPEN_FLAG O_RDWR|O_CREAT
#define OPEN_MODE 00777
#define FILE_SIZE 4096*4


int main(void)
{
    int ret = -1;
    int fd = -1;

    char buf[4096] = {0};
    void* add_r = NULL;

    //�������ߴ�һ�������ڴ�
    fd = shm_open(SHMNAME, OPEN_FLAG, OPEN_MODE);
    if(-1 == (ret = fd))
    {
        perror("shm  failed: ");
        goto _OUT;
    }
   
    //����ȷ���ļ������ڴ�Ŀռ�
    ret = ftruncate(fd, FILE_SIZE);
    if(-1 == ret)
    {
        perror("ftruncate faile: ");
        goto _OUT;
    }
    
    //ӳ��Ŀ���ļ��Ĵ洢��
    add_r = mmap(NULL, FILE_SIZE, PROT_READ, MAP_SHARED, fd, SEEK_SET);
    if(NULL == add_r)
    {
        perror("mmap add_r failed: ");
        goto _OUT;
    }


    //memcpy �ڴ湲�� д������
    memcpy(buf, add_r, sizeof(buf));
    
    printf("buf = %s\n", buf);

    //ȡ��ӳ��
    ret = munmap(add_r, FILE_SIZE);
    if(-1 == ret)
    {
        perror("munmap add_r faile: ");
        goto _OUT;
    }

    //ɾ���ڴ湲��
    shm_unlink(SHMNAME);
    if(-1 == ret)
    {
        perror("shm_unlink faile: ");
        goto _OUT;
    }

_OUT:    
    return ret;
}


