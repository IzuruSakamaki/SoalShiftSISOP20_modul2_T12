#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <wait.h>

int main(int argc, char const *argv[]) {
  if (argc != 2) {
    printf("Wrong Argument\n");
    exit(EXIT_FAILURE);
  }
  if (strcmp(argv[1], "-a") != 0 && strcmp(argv[1], "-b") != 0) {
    printf("Second Argument must specify mode (-a/-b)\n");
    exit(EXIT_FAILURE);
  }
  pid_t pid = fork(), sid;
  time_t t, s;
  struct tm *tm, *sm;
  if (pid < 0) exit(EXIT_FAILURE);
  if (pid > 0) exit(EXIT_SUCCESS);
  umask(0);
  sid = setsid();
  if (sid < 0) exit(EXIT_FAILURE);
  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);
  FILE *f;
  f = fopen("killer.c", "w");
  fprintf(f, "#include <unistd.h>\n#include <wait.h>\n\nint main() {\n  if (fork() == 0) {\n");
  if (strcmp(argv[1], "-a") == 0) fprintf(f, "    execl(\"/usr/bin/pkill\", \"pkill\", \"-9\", \"-s\", \"%d\", NULL);\n", sid);
  if (strcmp(argv[1], "-b") == 0) fprintf(f, "    execl(\"/usr/bin/kill\", \"kill\", \"-9\", \"%d\", NULL);\n", getpid());
  fprintf(f, "  }\n  while(wait(NULL) > 0);\n  execl(\"/usr/bin/rm\", \"rm\", \"killer\", NULL);\n}");
  fclose(f);
  if ((pid = fork()) == 0) execl("/usr/bin/gcc", "gcc", "killer.c", "-o", "killer", NULL);
  while(wait(NULL) != pid);
  if (fork() == 0) execl("/usr/bin/rm", "rm", "killer.c", NULL);
  int start = time(NULL)%30;
  while (1) {
    if ((time(NULL)%30) == start) {
      t = time(NULL);
      tm = localtime(&t);
      char dir[50], tmpdir[150], url[50], file[50];
      strftime(dir, 50, "khusus/%Y-%m-%d_%H:%M:%S", tm);
      if (fork() == 0) execl("/usr/bin/mkdir", "mkdir", "-p", dir, NULL);
      if (fork() == 0) {
        for (int i = 0; i < 20; i++) { // BE CAREFUL!!
          s = time(NULL);
          sm = localtime(&s);
          strcpy(tmpdir, dir);
          strftime(file, 50 ,"/%Y-%m-%d_%H:%M:%S" ,sm);
          strcat(tmpdir, file);
          sprintf(url, "https://picsum.photos/%ld", ((s % 1000) + 100));
          if (fork() == 0) execl("/usr/bin/wget", "wget", "-qbO", tmpdir, "-o", "/dev/null", url, NULL);
          sleep(5);
        }
        execl("/usr/bin/zip", "zip", "-rm", dir, dir, NULL);
      }
    }
    sleep(1);
  }
}
