#include "shell.h"
#include<readline/readline.h>
#include<readline/history.h>



int read_command(char **command, char **parameters, char *prompt) 
{ 
	extern char *buf;
	buf = readline(prompt);


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
			while(p != start && *p != '/')
				p--;
			if (*p == '/')
				p++;
			parameters[0] = p;
			
			
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


	return count;
}


