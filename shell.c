#include "shell.h"

#define TRUE 1 
#define MAX_CHILD 10
#define MAX_PROMPT 256
pid_t child_pid[MAX_CHILD];

void sig_handler()
{
	pid_t childpid;
	int i;
	for(i = 0; i < MAX_CHILD; ++i) 
	{
		childpid = waitpid(child_pid[i], NULL, WNOHANG);
		if (childpid > 0) {
			printf("process : %u exited\n", childpid);
			child_pid[i]  = 0;
		}
		else if (childpid < 0) {
			if (errno != ECHILD)
			    printf("waitpid error");
		}
		
	}
	return;
}


void loop(void)
{
	struct parse_info info;
	int pipe_fd[2], out_fd, in_fd;
	char promptbuf[MAX_PROMPT];
	pid_t childpid1, childpid2;
	int status; 
	char *command = NULL;
	char **parameters = malloc(sizeof(char *) * ARG_MAX);
	extern char *buf;
        buf = malloc(sizeof(char) * MAXARG);
       
	if (buf == NULL || parameters == NULL) {
		printf("buf and parameters malloc error\n");
		return;
	}

	if (signal(SIGCHLD, sig_handler) == SIG_ERR)
		printf("signal error");	
	while(TRUE) {
		prompt(promptbuf);
		int paranum = read_command(&command, parameters, promptbuf);

		if (paranum < 0) {
			printf("read_command error");
			continue;
		}
		paranum--;
		parse(parameters, paranum, &info);

		if (builtin_command(command, parameters))
		        continue;
		if (info.flags & PIPED) {
			if (pipe(pipe_fd) < 0) {
				printf("pipe error");
				exit(0);
			} 
		}
		if ((childpid1 = fork()) != 0) {
			if (info.flags & PIPED) {
				if((childpid2 = fork()) == 0) {
					close(pipe_fd[1]);
					close(fileno(stdin));
					dup2(pipe_fd[0], fileno(stdin));
					close(pipe_fd[0]);
					execvp(info.cmd2, info.parameters2);
				} else {
					close(pipe_fd[0]);
					close(pipe_fd[1]);
					waitpid(childpid2, &status, 0);
				}
			}
			if (info.flags & BACKGROUND) {
				printf("chile pid : %u\n", childpid1);
				int i ;
				for(i = 0; i < MAX_CHILD; ++i) {
					if(child_pid[i] == 0) {
						child_pid[i] = childpid1;		
						break;
					}
				}
				if (i == MAX_CHILD) 
					printf("too much childpid");
			}
			else {
				waitpid(childpid1, &status, 0);
			}

		} else {
			if (info.flags & PIPED) {
				if (!(info.flags & OUT_REDIRECT) && !(info.flags & OUT_REDIRECT_APPEND)) {
					close(pipe_fd[0]);
					close(fileno(stdout));
					dup2(pipe_fd[1], fileno(stdout));
					close(pipe_fd[1]);
				} else {
					close(pipe_fd[0]);
					close(pipe_fd[1]);
					if (info.flags & OUT_REDIRECT)
						out_fd = open(info.out_file, O_WRONLY|O_TRUNC|O_CREAT, 0666);
					if (info.flags & OUT_REDIRECT_APPEND) 
						out_fd = open(info.out_file, O_WRONLY|O_APPEND|O_TRUNC, 0666);
					close(fileno(stdout));
					dup2(out_fd, fileno(stdout));
					close(out_fd);
				}
				
			} else {
				if(info.flags & OUT_REDIRECT) {
					out_fd = open(info.out_file, O_WRONLY|O_TRUNC|O_CREAT, 0666);
					close(fileno(stdout));
					dup2(out_fd, fileno(stdout));
					close(out_fd);
				}
				if(info.flags & OUT_REDIRECT_APPEND) {
					out_fd = open(info.out_file, O_WRONLY|O_APPEND|O_TRUNC, 0666);
					close(fileno(stdout));
					dup2(out_fd, fileno(stdout));
					close(out_fd);
				}
			}
			if(info.flags & IN_REDIRECT) {
				in_fd = open(info.in_file, O_RDONLY|O_CREAT, 0666);
				close(fileno(stdin));
				dup2(in_fd, fileno(stdin));
				close(in_fd);
			}
			execvp(command, parameters);
			exit(0);
		}
	}
	free(parameters);
	free(buf);



}

int main()
{
	int i;
	for(i = 0; i < MAX_CHILD; ++i)
		child_pid[i] = 0;
	loop();
	return 0;
}
