#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>

int main(){

auto rc = fork();
int x = 100;

if(rc < 0){
printf("Issue while forking");

}else if (rc == 0){
//child process
x=50;
printf("%d\n",x);


} else{
//parent process
wait(NULL);
printf("%d\n",x);

}

return 0;
}
