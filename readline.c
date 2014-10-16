#include<readline/readline.h>
#include<readline/history.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h> 
#include <errno.h>
#include <pwd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h> 
#define ARG_MAX 1024
char *buf;

int read_command(char **command, char **parameters) 
{ 
	char *tempbuf = buf;
	buf = readline(NULL);
     /*   
        if(feof(stdin) == 0) {
		printf("\n");
		exit(0);
	}
	*/
	if (buf[0] == '\0')
		return -2;
	
	char *start, *end;
	int count = 0;
	start = end = buf;
	int isFinished = 0;
	while(isFinished != 1)
	{
		while((*end == ' ' && *start == ' ') || (*end == '\t' && *start == '\t')) 
		{
			end++;
			start++;
		}
		if(*end == '\0' || *end == '\n') {
			if(count == 0)
				return -3;
			break;
		}

	        while(*end != ' ' && *end != '\0' && *end != '\t')
			end++; 
	    
		if(count == 0) {
			*command = start;
			char *p = end;
			while(p != end && *p != '/')
				p--;
			if (*p == '/')
				p++;
			parameters[0] = p;
			printf("%s",*command);
			count += 2;


		} 

		else if (count <= ARG_MAX) {
			parameters[count - 1] = start;
			count++;
		}
		else
			break;
		if (*end == '\0' || *end == '\n') {
			isFinished = 1;
			*end = '\0';
		} else {
			*end = '\0';
			end++;
			start = end;
		}
        }
	
	parameters[count -1] = NULL;
	printf("input analysis:\n");
	    printf("pathname:%s\ncommand:%s\nparameters:\n",*command,parameters[0]);
	        int i;
		    for(i=0;i<count-1;i++)
		            printf("%s\n",parameters[i]);
	free(buf);
	buf = tempbuf;


	return 0;
}

int main()
{
	char *command = NULL; char  **parameters;
	parameters = (char **)malloc(sizeof(char *)*(ARG_MAX+2));
	char *buf = malloc(sizeof(char) * ARG_MAX);      
        int count = read_command(&command, parameters);
	printf("%d", count);

	return 0;
}

