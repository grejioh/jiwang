// 参考https://blog.csdn.net/qq_41122796/article/details/80396776
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
void func1(int hello) {
  printf("\n\tI received a signal, and my pid is %d\n\n", getpid());
}
int main() {
  signal(SIGUSR2, func1);

  pid_t pid;
  pid = fork();
  // 创建子进程
  if (pid == 0) {
    printf("In Child Process:\nThis process will send a signal to parent.\n");
    printf("My pid is %d.\nparent's pid is %d.\nChild process finished.\n",
           getpid(), getppid());
    kill(getppid(), SIGUSR2);
  } else if (pid >= 1) {
    waitpid(pid, NULL, 0);
    printf("In Parent Process:\n");
    printf("My pid is %d.\n", getpid());
    printf("Parent Process end\n");
  } else {
    printf("failed to create a child process\n");
  }
  return 0;
}
