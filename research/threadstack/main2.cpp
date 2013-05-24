// #define _GNU_SOURCE
 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #include <pthread.h>
 
 static void *th_fn(void *arg);
 
 int main(int argc, char *argv[])
 {
     int ret;
     pthread_attr_t attr;
     pthread_t thid;
     void *stackaddr;
     size_t stacksize;
 
     if ((ret = pthread_attr_init(&attr)) != 0) {
         fprintf(stderr, "pthread_attr_init error: %s\n", strerror(ret));
         exit(EXIT_FAILURE);
     }
 
     if ((ret = pthread_attr_getstack(&attr, &stackaddr, &stacksize)) != 0) {
         fprintf(stderr, "pthread_attr_getstack error: %s\n", strerror(ret));
         exit(EXIT_FAILURE);
     }
     printf("init attr: stackaddr = %p, stacksize = %d\n", stackaddr, stacksize);
 
     if ((ret = pthread_create(&thid, &attr, th_fn, NULL)) != 0) {
         fprintf(stderr, "pthread_create error: %s\n", strerror(ret));
         exit(EXIT_FAILURE);
     }
 
     if ((ret = pthread_getattr_np(thid, &attr)) != 0) {
         fprintf(stderr, "pthread_getattr_np error: %s\n", strerror(ret));
         exit(EXIT_FAILURE);
     }
 
     if ((ret = pthread_attr_getstack(&attr, &stackaddr, &stacksize)) != 0) {
         fprintf(stderr, "pthread_attr_getstack error: %s\n", strerror(ret));
         exit(EXIT_FAILURE);
     }
     printf("thread attr: stackaddr = %p, stacksize = %d\n", stackaddr, stacksize);
 
     if ((ret = pthread_attr_destroy(&attr)) != 0) {
         fprintf(stderr, "pthread_attr_destroy error: %s\n", strerror(ret));
         exit(EXIT_FAILURE);
     }
 
     exit(EXIT_SUCCESS);
 }
 
 static void *th_fn(void *arg)
 {
     while (1)
         continue;
     pthread_exit((void *)1);
 }
