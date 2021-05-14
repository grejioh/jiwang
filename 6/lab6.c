#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

sem_t *empty, *full, *mutex;
FILE *fp;

void Producter(FILE *fp) {
  int i;
  for (i = 1; i <= 233; i++) {
    sem_wait(empty);
    sem_wait(mutex);
    int rd = rand() % 1000;
    fseek(fp, sizeof(int), SEEK_SET);
    fwrite(&rd, sizeof(int), 1, fp);
    fflush(fp);
    printf("give: %d \n", rd);
    sem_post(mutex);
    sem_post(full);
  }
}
void Customer(FILE *fp) {
  for (int i = 1; i <= 233; i++) {
    sem_wait(full);
    sem_wait(mutex);
    int output;
    fseek(fp, sizeof(int), SEEK_SET);
    fread(&output, sizeof(int), 1, fp);
    printf("consumer[pid:%d] get: %d\n", getpid(), output);
    fflush(fp);
    sem_post(mutex);
    sem_post(empty);
  }
}
int main() {
  pid_t producter;
  pid_t customer;
  empty = sem_open("empty", O_CREAT, 0777, 1);
  full = sem_open("full", O_CREAT, 0777, 0);
  mutex = sem_open("mutex", O_CREAT, 0777, 1);
  fp = fopen("./txt.txt", "wb+");

  producter = fork();
  if (producter != 0) {
    Producter(fp);
  } else {
    customer = fork();
    if (customer == 0) {
      Customer(fp);
    }
  }
  sem_unlink("empty");
  sem_unlink("full");
  sem_unlink("mutex");
  fclose(fp);
  return 0;
}
