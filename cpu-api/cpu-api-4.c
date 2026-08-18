#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> //file control options
#include <err.h>

int main(){
 int cpid = fork();
 if (cpid < 0){
  printf("failed to fork");
 }else if(cpid == 0){
  char *argv[2];
  argv[0] = "ls";
  argv[1] = NULL;
  execlp(argv[0], argv[1]);
 }else{
  char *argv[2];
  argv[0] = "ls";
  argv[1] = NULL;
  execlp(argv[0], argv[1]);
 }
return 0;
}
