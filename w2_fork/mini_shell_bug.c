#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
  
int main() {
    char *argv[10];
	char str[256];
    while(1) {
        int iter = 0;
        printf("h94usu6@DESKTOP-I4M9KKH:/mnt/c/Users/User/Desktop/light_dance/RPi-learn/w2_fork$ ");
        scanf("%[^\n]", str);

        char *token;
        token = strtok (str," ");
        while (token != NULL) {
            // printf("%s",token);
            argv[iter] = token;
            iter++;
            token = strtok (NULL, " ");
            if(token == NULL) {
                argv[iter] = NULL;
                break;
            }
        }

        pid_t pid = fork();
        if(pid == 0) {
            execvp(argv[0], argv);
        }
        else {
            wait(0);
        }
        // break;
    }
    return 0;
}