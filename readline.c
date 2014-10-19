#include "shell.h"
#include<readline/readline.h>
#include<readline/history.h>



int read_command(char **command, char **parameters, char *prompt) 
{ 
	extern char *buf;
	buf = readline(prompt);
        /*
        if(feof(stdin) == 0) {
		printf("\n");
		exit(0);
	}
	*/
	if (buf[0] == '\0')
		return -1;
	
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
				return -1;
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
			
			
			count += 2;
			//printf("parameters[0]:%s", parameters[0]);
                         

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
	    printf("command:%s\nparameters:%s\n",*command,parameters[0]);
	        int i;
		    for(i=0;i<count-1;i++)
       
        	            printf("%s\n",parameters[i]);
	

	return count;
}
/*
int main()
{
	char *command = NULL; char  **parameters;
	parameters = (char **)malloc(sizeof(char *)*(ARG_MAX+2));
	char *buf = malloc(sizeof(char) * ARG_MAX);      
        int count = read_command(&command, parameters);
	printf("%d", count);

	return 0;
}
 */

