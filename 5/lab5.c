// 参考https://www.cnblogs.com/sparkdev/p/11008978.html
#include <fcntl.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define FIFO_NAME "./testp"
#define BUFFER_SIZE 10000
#define TEN_MEG (1024 * 1024 * 10)
int main() {
  int pipe_fd;
  int res;
  int open_mode = O_RDWR; // 只写
  int bytes_sent = 0;

  if (access(FIFO_NAME, F_OK) == -1) {
    res = mkfifo(FIFO_NAME, 0777); // rwxrwxrwx
    if (res != 0) {
      fprintf(stderr, "Could not create fifo %s\n", FIFO_NAME);
      exit(EXIT_FAILURE);
    }
  }

  pipe_fd = open(FIFO_NAME, open_mode); // 返回文件描述符
  printf("Parent Process (pid:%d) opened FIFO.\n", getpid());
  printf("FIFO fd: %d\n", pipe_fd);

  pid_t pid;
  pid = fork();

  if (pipe_fd == -1) {
    exit(EXIT_FAILURE);

  } else if (pid < 0) {
    perror("fork error");
    return -1;
  } else if (pid == 0) {
    printf("In Child Process:\n writing...\n");
    printf("My pid:%d\nParent's pid:%d\n", getpid(), getppid());
    sleep(1);
    char buffer[] = "Hello!";
    write(pipe_fd, buffer, strlen(buffer));
    close(pipe_fd);

  } else if (pid > 0) {
    waitpid(pid, NULL, 0);
    char buffer[10000];
    read(pipe_fd, buffer, 10000);
    printf("In Parent process:\n received: \"%s\"\n", buffer);
  }
  return 0;
}
