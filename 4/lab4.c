// 参考https://blog.csdn.net/W_J_F_/article/details/83789819
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
int main() {
  pid_t pid;
  int pipefd[2] = {0};
  if (pipe(pipefd) < 0) {
    perror("pipe error");
    return -1;
  }
  pid = fork();
  if (pid < 0) {
    perror("fork error");
    return -1;
  } else if (pid == 0) {
    printf("In Child Process:\n writing...\n");
    sleep(1);
    close(pipefd[0]);
    char buffer[] = "Boya";
    write(pipefd[1], buffer, strlen(buffer));
    close(pipefd[1]);
  } else if (pid > 0) {
    waitpid(pid, NULL, 0);
    close(pipefd[1]);
    char buffer[10000];
    read(pipefd[0], buffer, 10000);
    close(pipefd[0]);
    printf("In Parent process:\n received: \"%s\"\n", buffer);
  }
  return 0;
}
