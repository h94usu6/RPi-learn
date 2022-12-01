#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

/*
    char *argv[10];
	char str[256];
	int iter = 0;
	scanf("%[^\n]", str);
	char *token;
	token = strtok (str," ");
	while (token != NULL) {
		argv[iter] = token;
		iter++;
		token = strtok (NULL, " ");
		if(token == NULL) {
			argv[iter] = NULL;
		}
	}
	execvp(argv[0],argv);
*/

int main() {
    char *argv[10];
    char command[1024];
    while(1) {
        int iter = 0;
        printf("h94usu6@DESKTOP-I4M9KKH:/mnt/c/Users/User/Desktop/light_dance/RPi-learn/w2_fork$ ");
        fgets(command, (int)sizeof(command), stdin);

        char *s = command;
        while (1) {
            int i = 0;
            while(s[i] != ' ' && s[i] != '\n') i++;

            argv[iter] = malloc(i);
            strncpy(argv[iter], s, i);
            iter++;

            s += i;
            if(*s == '\n') break;
            s++;
        }
        argv[iter] = NULL;

        pid_t pid = fork();
        if(pid == 0) {
            execvp(argv[0],argv);
        }
        else {
            wait(0);
        }
    }
    return 0;
}