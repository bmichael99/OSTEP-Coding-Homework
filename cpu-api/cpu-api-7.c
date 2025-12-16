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
 int pipefd[2];
 if(pipe(pipefd) == -1){
  printf("error creating pipe");
 }
 int cpid[2];
 cpid[0] = fork();
 if(cpid[0] < 0){
  printf("error while  forking");
 }else if(cpid[0] == 0){
  //first child
  close(pipefd[0]); //close unused read end  
  dup2(pipefd[1],STDOUT_FILENO); //dup2 closes STDOUT_FILENO silently before referring STDOUT to pipefd[1].
  close(pipefd[1]);
  const char* msg = "printing in first child";
  write(STDOUT_FILENO, msg,strlen(msg));
 }else{
  //parent process
  printf("printing in parent\n");
  cpid[1] = fork();
  if(cpid[1] < 0){
   printf("error while forking second child");
  }else if(cpid[1] == 0){
   //second child
   close(pipefd[1]);
   char buff[256];
   dup2(pipefd[0],STDIN_FILENO); //silently closes STDIN before referring STDIN to pipefd[0]
   close(pipefd[0]);
   read(STDIN_FILENO,buff,256); //read through the STDIN that's hooked up to the pipe
   printf("printing in second child, output from first child: %s\n",buff);
  }else{
   waitpid(cpid[0],NULL,0);
   waitpid(cpid[1],NULL,0);
  }
 }
return 0;
}
