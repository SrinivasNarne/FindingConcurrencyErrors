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

  printf("\nThe FIRST thread opens in Mode 2 and then the thread is killed.\n");

  fd_1 = open("/dev/a5", O_RDWR);
  printf("OPEN from FIRST thread.\n");

  sleep(10);

  printf("Killing the FIRST thread.\n");
  pthread_exit(NULL);

  close(fd_1);
  printf("CLOSE from FIRST thread.\n");

}

void *pthread_method_two(void *arg) {

  int fd_2;
  int err_check;

  printf("\n The SECOND thread opens in Mode 2 and calls ioctl in Mode 1 after the first thread is killed.\n");

  fd_2 = open("/dev/a5", O_RDWR);
  printf("OPEN from SECOND thread.\n");

  sleep(10);

  err_check = ioctl(fd_2, E2_IOCMODE1, 1);
  if (err_check == -1) {
    perror("ERROR: Ioctl error in SECOND thread.\n");
  }
  printf("IOCTL from SECOND thread.\n");

  close(fd_2);
  printf("CLOSE from SECOND thread.\n");

}

int main(int argc, char *argv[]) {

  int fd;
  int err_check;

  fd = open("/dev/a5", O_RDWR);
  err_check = ioctl(fd, E2_IOCMODE2, 2);
  if (err_check == -1) {
    perror("ERROR: Ioctl error in MAIN.\n");
  }
  printf("\nSetting initial Mode to MODE 2.\n");

  close(fd);

  pthread_create(&pthread1, NULL, pthread_method_one, (void*)(0));
  printf("Created THREAD 1.\n");
  sleep(5);
  pthread_create(&pthread2, NULL, pthread_method_two, (void*)(1));
  printf("Created THREAD 2. \n");

  pthread_join(pthread1, NULL);
  pthread_join(pthread2, NULL);

  return 0;
}
