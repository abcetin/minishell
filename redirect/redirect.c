#include "../minishell.h"

int is_exist_file(char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	return (1);
}

int create_file(char *path)
{
	int fd;

	if (!is_exist_file(path))
		fd = open(path, O_RDWR | O_CREAT);
	else
		fd = open(path, O_RDWR);
	if (fd == -1)
	{
		perror("");
		return (0);
	}
	return (fd);
}

void clear_file(char *path)
{
	int fd;
	fd = open(path, O_TRUNC);
	if (fd < 0)
		perror("");
}

void single_right_redirect(char *cmd, char **path)
{
	int file;
	int pid;
	int i;

	i = 0;
	while (path[i])
	{
		if (is_exist_file(path[i]))
			clear_file(path[i]);
		file = create_file(path[i]);
		pid = fork();
		if (pid == 0)
		{
			dup2(file, 1);
			close(file);
			parse_string(cmd);
		}
		wait(NULL);
		i++;
	}
}


// int main()
// {
// 	char *path[3] = {"asd.txt jahsgdjgasghd", "deneme.txt jhasdjhgasjgd", NULL};
// 	char *cmd = "echo deniz > test.txt askdalks";
// 	int len = char_count(cmd, '>');

// }