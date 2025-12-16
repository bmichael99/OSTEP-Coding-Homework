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
//we will print into cpu-api-3.output, we could also just printf instead  
int fd = open("./cpu-api-3.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
int pipefd[2]; //returns two file descriptors pipefd[0]=read,pipefd[1]=write
if(pipe(pipefd) == -1){ //pass array of size 2 into pipe to get back piped fd
err(EXIT_FAILURE, "pipe");
}

int rc = fork();
if(rc < 0){
printf("Issue while forking");
}else if (rc == 0){
//child process
  close(pipefd[0]);//close read fd, not needed in this process
  const char *msg = "hello\n";
  size_t size = strlen(msg);
  write(fd, msg, size);
  write(pipefd[0],msg,size);
} else{
//parent process
  close(pipefd[1]);//close write fd, not needed in this process
  const size_t buffer_size = 4096;
  char buffer[buffer_size];
  //if there is no data in the pipe, than this process will block
  read(pipefd[0],buffer,buffer_size);

  const char *msg = "goodbye\n";
  size_t size = strlen(msg);
  write(fd, msg, size);
}

return 0;
}
