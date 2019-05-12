#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <pthread.h>

void *timer(char *fname, char *mi, char *h, char *d, char *mo, char *w){
    //char *mi,*h,*d,*mo,*w;
    //char *fname;

    //*fname = *((char *)f);
    //*mi = *((char *)o);
    //*h = *((char *)p);
    //*d = *((char *)q);
    //*mo = *((char *)r);
    //*w = *((char *)s);

    time_t curtime;
    struct tm *loc_time, *after_time;
    time(&curtime);
    after_time = localtime(&curtime);

    char timeStrB[255];
    char timeStrA[255];
    strftime(timeStrB, sizeof(timeStrB), "%a %D %H:%M:%S", after_time);
    //printf("Time now: %s\n", timeStrB);

    if (strcmp(mi,"*")==0);
        else after_time->tm_min += atoi(mi) ;
    if (strcmp(h,"*")==0);
        else after_time->tm_hour += atoi(h);
    if (strcmp(d,"*")==0);
        else after_time->tm_mday += atoi(d);
    if (strcmp(mo,"*")==0);
        else after_time->tm_mon += atoi(mo);
    if (strcmp(w,"*")==0);
        else after_time->tm_wday = atoi(w);

    strftime(timeStrA, sizeof(timeStrA), "%a %D %H:%M:%S", after_time);

    while (strcmp(timeStrA,timeStrB)!=0){
        sleep(1);
    } 

    system("fname");
    //printf("Time after: %s\n", timeStrA);
    //printf("%d\n",atoi(h));

}


int main() {
  pid_t pid, sid;

  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();

  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  if ((chdir("/")) < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  pthread_t threads[300];
  int i = 0;

  while(1) {
    FILE *input = fopen("crontab.data","r");
    char file, i, h, d, o, w;

    if (input == NULL){
        exit(-1);
    }

    while (fscanf(input, "%c %c %c %c %c %c",&file,&i,&h,&d,&o,&w) == 1){
        //pthread_create(&(threads[i]), NULL, timer, &file,&i,&h,&d,&o,&w);
	timer(file,i,h,d,o,w);
        i++;
    }
  }
}

