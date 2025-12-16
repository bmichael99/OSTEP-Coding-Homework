#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> //file control options

int main(){
int fd = open("./cpu-api-2.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);
auto rc = fork();

if(rc < 0){
printf("Issue while forking");
}else if (rc == 0){
//child process
const char *msg = "Child Process!\n";
size_t size = strlen(msg);
write(fd, msg, size);
} else{
//parent process
//wait(NULL);
const char *msg = "Parent Process!\n";
size_t size = strlen(msg);
write(fd, msg, size);
}

return 0;
}
