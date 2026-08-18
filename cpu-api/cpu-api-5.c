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
 int status;
 int pid = getpid();
 printf("Parent PID: %d\n",pid); 
 int cpid = fork();
 printf("Child PID: %d\n", cpid);
 if(cpid < 0){
  printf("error while forking");
  
 }else if(cpid == 0){
  //pid_t res = wait(NULL);
  //printf("in child: %d", res);
  pid_t waitpid_return = waitpid(-1, NULL, WUNTRACED | WCONTINUED);
  printf("child wait return: %d\n", waitpid_return);
 }else{
  pid_t res = waitpid(cpid,&status, WUNTRACED | WCONTINUED);
  printf("in parent: %d\n",res);

  if(WIFEXITED(status) == 1){
   printf("Child exited successfully\n");
  }
  if(WIFSIGNALED(status) == 1){
   printf("Child was terminated by a signal\n");
  }
}
 return 0;
}
