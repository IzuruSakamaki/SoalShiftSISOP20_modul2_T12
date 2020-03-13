#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main (int argc, char *argv[]) {
  if (argc != 5) {
    printf("Wrong Argument\n");
    exit(EXIT_FAILURE);
  }
  if (!(((atoi(argv[1]) >= 0) && (atoi(argv[1]) < 60)) || ((strcmp(argv[1],"*")) == 0))) {
    printf("First Argument must between 0-59 or *\n");
    exit(EXIT_FAILURE);
  }
  if (!(((atoi(argv[2]) >= 0) && (atoi(argv[2]) < 60)) || ((strcmp(argv[2],"*")) == 0))) {
    printf("Second Argument must between 0-59 or *\n");
    exit(EXIT_FAILURE);
  }
  if (!(((atoi(argv[3]) >= 0) && (atoi(argv[3]) < 24)) || ((strcmp(argv[3],"*")) == 0))) {
    printf("Third Argument must between 0-23 or *\n");
    exit(EXIT_FAILURE);
  }
  int ext = strlen(argv[4]);
  if (!(((&(argv[4][ext--]) == "h") || (&(argv[4][ext]) == "H")) && ((&(argv[4][ext--]) == "s") || (&(argv[4][ext]) == "S")) && (&(argv[4][ext--]) == "."))) {
    printf("Forth Argument must be shell script\n");
    exit(EXIT_FAILURE);
  }
  time_t t;
  struct tm tm;
  pid_t pid = fork(), sid;
  if (pid < 0) exit(EXIT_FAILURE);
  if (pid > 0) exit(EXIT_SUCCESS);
  umask(0);
  sid = setsid();
  if (sid < 0) exit(EXIT_FAILURE);
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  while (1) {
    t = time(NULL);
    tm = *localtime(&t);
    if ((tm.tm_sec == atoi(argv[1]) || ((strcmp(argv[1],"*")) == 0)) && (tm.tm_min == atoi(argv[2]) || ((strcmp(argv[2],"*")) == 0)) && (tm.tm_hour == atoi(argv[3]) || ((strcmp(argv[3],"*") == 0)))) {
      if (fork()==0) {
        execl("/bin/bash", "bash", argv[4], NULL);
        sleep(1);
      }
    }
  }
}
