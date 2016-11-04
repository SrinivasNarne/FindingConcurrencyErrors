#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<unistd.h>
#include<fctnl.h>
#include<linux/ioctl.h>
#include<sys/ioctl.h>
#include<string.h>
#include<time.h>
#include<signal.h>

#define CDRV_IOC_MAGIC 'Z'
#define E2_IOCMODE1 _IOWR(CDRV_IOC_MAGIC, 1, int)
#define E2_IOCMODE2 _IOWR(CDRV_IOC_MAGIC, 2, int)

pthread_t pthread1, pthread2; // Initializing the two pthreads

void *pthread_method_one(void *arg) {

  int fd_1;
  int err_check;

  printf("\n The FIRST thread opens in Mode 1 and calls ioctl in Mode 2 after the second thread opens.\n");

  fd_1 = open("/dev/a5", O_RDWR);
  printf("OPEN from FIRST thread.\n");

  sleep(10);

  err_check = ioctl(fd_1, E2_IOCMODE1, 2);
  if (err_check == -1) {
    perror("ERROR: Ioctl error in FIRST thread.\n");
  }
  printf("IOCTL from FIRST thread.\n");

  close(fd_1);
  printf("CLOSE from FIRST thread.\n");

}

void *pthread_method_two(void *arg) {

  FILE *fp;

  fp = fopen("/dev/a5", "w+");
  printf("OPEN from SECOND thread.\n");

  fclose(fp);
  printf("CLOSE from SECOND thread.\n");

}

int main(int argc, char *argv[]) {

  pthread_create(&pthread1, NULL, pthread_method_one, (void*)(0));
  printf("Created THREAD 1.\n");
  sleep(5);
  pthread_create(&pthread2, NULL, pthread_method_two, (void*)(1));
  printf("Created THREAD 2. \n");

  pthread_join(pthread1, NULL);
  pthread_join(pthread2, NULL);

  return 0;
}
