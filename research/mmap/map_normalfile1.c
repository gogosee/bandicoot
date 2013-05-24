#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
typedef struct{
  char name[10];
  int  age;
}people;

main(int argc, char** argv) // map a normal file as shared mem:
{
  int fd,i;
  people *p_map;
  char temp;
  
  fd=open(argv[1],O_CREAT|O_RDWR|O_TRUNC,00777);
  lseek(fd,sizeof(people)*10000-1,SEEK_SET);	// ÎÄ¼þ¿Õ¶´
  lseek(fd, 0, SEEK_SET);
  write(fd,"",1);
  
  p_map = (people*) mmap( NULL,sizeof(people)*10000,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0 );
  close( fd );

  temp = 'a';
  for(i=0; i<10000; i++)
  {
    temp += 1;
	memset(p_map+i, 0, sizeof(people));
    //memcpy( ( *(p_map+i) ).name, &temp,2 );
	snprintf( (*(p_map+i) ).name, sizeof((*(p_map+i) ).name), "name_%d", i);
    ( *(p_map+i) ).age = i;
	printf("i: %d\n", i);
	sleep(1);
  }
  printf(" initialize over \n ");
  sleep(10);
  munmap( p_map, sizeof(people)*10 );

  printf( "umap ok \n" );
}


