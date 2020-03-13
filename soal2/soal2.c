#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
// #include <fcntl.h>
// #include <errno.h>
#include <unistd.h>
// #include <syslog.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main(int argc, char const *argv[]) {
  pid_t pid, sid, wpid, pidmain, pidb, pidc, pidd, pide;
  pid = fork();
  time_t t, s;
  struct tm *tm, *sm;
  int status = 0;
  if (pid < 0) exit(EXIT_FAILURE);
  if (pid > 0) exit(EXIT_SUCCESS);
  umask(0);
  sid = setsid();
  if (sid < 0) exit(EXIT_FAILURE);
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  int start = time(NULL)%30;
  while (1) {
    if ((time(NULL)%30) == start) {
      pidmain = fork();
      t = time(NULL);
      tm = localtime(&t);
      char dir[50], tmpdir[150], url[50], file[50];
      strftime(dir, 50, "khusus/%Y-%m-%d_%H:%M:%S", tm);
      if ((pidb=fork())==0) execl("/usr/bin/mkdir", "mkdir", "-p", dir, NULL);
      if ((pidc=fork())==0) {
        for (int i = 0; i < 2; i++) {
          s = time(NULL);
          sm = localtime(&s);
          strcpy(tmpdir, dir);
          strftime(file, 50 ,"/%Y-%m-%d_%H:%M:%S" ,sm);
          strcat(tmpdir, file);
          sprintf(url, "https://picsum.photos/%ld", ((s % 1000) + 100));
          if ((pidd=fork())==0) execl("/usr/bin/wget", "wget", "-O", tmpdir, url, NULL);
        exit(0);
      }
      while ((wpid = wait(&status)) > 0);
      if ((pide=fork())==0) execl("/usr/bin/zip", "zip", "-rm", dir, dir, NULL);
      printf("pid: %d\nsid: %d\nwpid: %d\npidmain: %d\npidb: %d\npidc: %d\npidd: %d\npide: %d\n", pid, sid, wpid, pidmain, pidb, pidc, pidd, pide);
      }
    }
  }
}
