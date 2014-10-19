#include "shell.h"

void parse_info_init(struct parse_info *info)
{
	info->flags = 0;
	info->out_file = NULL;
	info->in_file = NULL;
	info->cmd2 = NULL;
	info->parameters2 = NULL;
	
	return;
}


int parse(char **parameters, int paranum, struct parse_info *info)
{
	int i;
	parse_info_init(info);
	if (strcmp(parameters[paranum - 1], "&") == 0) {
		info->flags |= BACKGROUND;
		parameters[paranum - 1] = NULL;
		paranum--;
	}

	for(i = 0; i < paranum;)
	{
		if ((strcmp(parameters[i], "<") == 0) || (strcmp(parameters[i], "<<") == 0)) {
			info->flags |= IN_REDIRECT;
			info->in_file = parameters[i + 1];
			parameters[i] = NULL;
			i += 2;
		}
		else if (strcmp(parameters[i], ">") == 0) {
			info->flags |= OUT_REDIRECT;
			info->out_file = parameters[i + 1];
			parameters[i] = NULL;
			i += 2;
		}
		else if (strcmp(parameters[i], ">>") == 0) {
			info->flags |= OUT_REDIRECT_APPEND;
			info->out_file = parameters[i + 1];
			parameters[i] = NULL;
			i += 2;
		}
		else if (strcmp(parameters[i], "|") == 0) {
			char *p;
			info->flags |= PIPED;
			info->cmd2 = parameters[i + 1];
			info->parameters2 = &parameters[i + 1];
			for(p = info->parameters2[0] + strlen(info->parameters2[0]);
				p != &(info->parameters2[0][0]) && *p != '/'; p --);
			if(*p == '/')
			    p++;
			info->parameters2[0] = p++;
			break;
		}
		else 
			i++;
	}
	return 1;
}
