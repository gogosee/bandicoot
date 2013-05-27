#include <cstdio>
#include <unistd.h>
#include <pthread.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/mman.h>


#define PRINTTRACE(szLogLevel, szLogStr, nRet)	\
		printf(szLogStr, nRet)

#define TCException(szExcStr)	0


class ShareRwlock
{
public:
    ShareRwlock();
    ~ShareRwlock();
    void WrLock();
    void RdLock();
    void UnLock();
private:
    pthread_rwlock_t* m_pRwlock;
};


ShareRwlock::ShareRwlock()
{
    m_pRwlock = ( pthread_rwlock_t* ) mmap ( NULL, sizeof ( pthread_rwlock_t ), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0 );
    pthread_rwlockattr_t attr_pub;
    pthread_rwlockattr_init ( &attr_pub );
    pthread_rwlockattr_setpshared ( &attr_pub, PTHREAD_PROCESS_SHARED );
    pthread_rwlock_init ( m_pRwlock, &attr_pub );
}

ShareRwlock::~ShareRwlock()
{
    pthread_rwlock_destroy ( m_pRwlock );
    munmap ( m_pRwlock, sizeof ( pthread_rwlock_t ) );
}

void ShareRwlock::WrLock()
{
#if 1
    int nRtn = 0;

    if ( ( nRtn = pthread_rwlock_wrlock ( m_pRwlock ) ) != 0 )
    {
		PRINTTRACE ( g_szError, "[ShareRwlock::WrLock]Error!Errno is %d", nRtn );
        throw TCException ( "ShareRwlock::WrLock() exception!" );
    }
#endif
}

void ShareRwlock::RdLock()
{
    int nRtn = 0;

    if ( ( nRtn = pthread_rwlock_rdlock ( m_pRwlock ) ) != 0 )
    {
        PRINTTRACE ( g_szError, "[ShareRwlock::RdLock]Error!Errno is %d", nRtn );
        throw TCException ( "ShareRwlock::RdLock() exception!" );
    }
}

void ShareRwlock::UnLock()
{
#if 1
    int nRtn = 0;

    if ( ( nRtn = pthread_rwlock_unlock ( m_pRwlock ) ) != 0 )
    {
        PRINTTRACE ( g_szError, "[ShareRwlock::UnLock]Error!Errno is %d", nRtn );
        throw TCException ( "ShareRwlock::UnLock() exception!" );
    }
#endif
}



#define SIZE 	1024
ShareRwlock 	m_ShareRwLock;
ShareRwlock* 	g_pub_rwlock = NULL;

int main()
{
	int pid = 0;
	g_pub_rwlock = &m_ShareRwLock;

	// share memory
    int shmid ;
    char *shmaddr ;
    struct shmid_ds buf ;
    int flag = 0 ;
    shmid = shmget(IPC_PRIVATE, SIZE, IPC_CREAT|0600 ) ;
    if ( shmid < 0 )
    {
            perror("get shm  ipc_id error") ;
            return -1 ;
    }

    pid = fork() ;
    if ( pid == 0 )
    {
		while(1)
		{
			printf("process %d block(value is b).\n", getpid());
			g_pub_rwlock->WrLock();
			printf("process %d get lock.\n", getpid());

	        shmaddr = (char *)shmat( shmid, NULL, 0 ) ;
 			if ( (int)shmaddr == -1 )
   			{
            	perror("shmat addr error") ;
           		return -1 ;
       		}
			
			shmaddr[0] = 'a';
        	shmdt( shmaddr ) ;

			usleep(5000 * 1000);
			g_pub_rwlock->UnLock();
			usleep(3100);
		}

	}
	else if ( pid > 0)
	{
	    pid = fork() ;
   		if ( pid == 0 )
   		{
			while(1)
			{
				printf("process %d block(value is a).\n", getpid());
				g_pub_rwlock->WrLock();
				printf("process %d get lock.\n", getpid());

		        shmaddr = (char *)shmat( shmid, NULL, 0 ) ;
	 			if ( (int)shmaddr == -1 )
	   			{
	            	perror("shmat addr error") ;
	           		return -1 ;
	       		}
			
				shmaddr[0] = 'b';
    	    	shmdt( shmaddr ) ;

				usleep(4000 * 1000);
				g_pub_rwlock->UnLock();
				usleep(1300);
			}
	
		}
		else if ( pid > 0)
		{
			while(1)
			{

        		shmaddr = (char *) shmat(shmid, NULL, 0 ) ;

        		if ( (int)shmaddr == -1 )
        		{
            		perror("shmat addr error") ;
            		return -1 ;
        		}

        		printf("shmaddr[0]: %c\n", shmaddr[0]) ;
        		shmdt( shmaddr ) ;

				sleep(1);
			}
		}
	}

	return 0;
}





