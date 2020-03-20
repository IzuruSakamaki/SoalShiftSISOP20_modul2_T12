#include <unistd.h>

int main() {
  if (fork() == 0) execl("/bin/mkdir", "mkdir", "-p","indomie", NULL);
  if (fork() == 0) execl("/usr/bin/unzip", "unzip", "-oq","jpg.zip", NULL);
  sleep(5);
  if (fork() == 0) execl("/bin/mkdir", "mkdir", "-p","sedaap", NULL);
  sleep(1);
  if(fork() == 0) execl("/usr/bin/find", "find", "jpg/", "-mindepth", "1", "-type", "f", "-exec", "mv", "-t", "sedaap/", "{}", "+", (char*)NULL);
  sleep(2);
  if(fork() == 0) execl("/usr/bin/find", "find", "jpg/", "-mindepth", "1", "-type", "d", "-exec", "mv", "-t", "indomie/", "{}", "+", (char*)NULL);
  if(fork() == 0) execl("/usr/bin/find", "find", "indomie/", "-type", "d", "-exec", "touch", "{}/coba1.txt", ";", NULL);
  sleep(3);
  if(fork() == 0) execl("/usr/bin/find", "find", "indomie/", "-type", "d", "-exec", "touch", "{}/coba2.txt", ";", NULL);
}
