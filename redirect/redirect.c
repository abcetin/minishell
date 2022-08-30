#include "../minishell.h"

int is_exist_file(char *path)
{
	if (access(path, F_OK) == -1)
		return (0);
	return (1);
}

int open_file(char *path)
{
	int fd;

	if (!path)
		return(-1);
	if (!is_exist_file(path))
		fd = open(path, O_RDWR | O_CREAT);
	else
		fd = open(path, O_APPEND | O_RDWR);
	if (fd == -1)
	{
		perror("asd2");
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
	close(fd);
}

int red_count(char *str)
{
	int i;
	int ret;

	ret = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && (str[i] == '<' || str[i] == '>'))
			i++;
		if (str[i] && !quote_state(str, i))
			ret++;
		while (str[i] && (str[i] != '<' && str[i] != '>'))
			i++;
	}
	return (ret);
}

int cut_red(char *dst, char **src)
{
	int i;

	i = 0;
	while (dst[i])
	{
		if ((dst[i] == '<' || dst[i] == '>') && !quote_state(dst, i))
			break;
		i++;
	}
	*src = ft_substr(dst, 0, i);
	return (i);
}

char **redirect_split(char *str)
{
	char **ret;
	int i;
	int ret_index;
	int len;

	i = 0;
	ret_index = -1;
	len = -1;
	ret = malloc(sizeof(char *) * (red_count(str) + 1));
	while (++len < red_count(str))
	{
		while (str[i] && (str[i] == '<' || str[i] == '>'))
			i++;
		if (str[i] != '<' && str[i] != '>')
			i += cut_red(&str[i], &ret[++ret_index]);
	}
	ret[++ret_index] = NULL;
	return (ret);
}



// static char **join_redirect(char **cmd)
// {
// 	int i;
// 	int j;
// 	char **temp;

// 	i = 1;
// 	while (cmd[i])
// 	{
// 		j = 1;
// 		temp = split2(cmd[i], 32);
// 		while (temp[j])
// 		{
// 			cmd[0] = ft_strjoin(cmd[0], " ");
// 			cmd[0] = ft_strjoin(cmd[0], temp[j]);
// 			free(cmd[i]);
// 			cmd[i] = ft_strdup(temp[0]);
// 			j++;
// 		}
// 		ft_free_double(temp);
// 		i++;
// 	}
// 	return (cmd);
// }

void right_redirect(char *cmd, char *file)
{
	int fd;
	int pid;

	pid = fork();
	if (pid == 0)
	{
		fd = open_file(file);
		if (fd < 0)
			exit(1);
		dup2(fd, STDOUT_FILENO);
		close(fd);
		parse_string(cmd);
		exit(0);
	}
	wait(NULL);
}

void single_right_redirect(char *cmd, char *file)
{
	char *temp;

	temp = ft_strtrim(file, " ");
	if (is_exist_file(temp))
		clear_file(temp);
	right_redirect(cmd, temp);
	free(temp);
}

void double_right_redirect(char *cmd, char *file)
{
	char *temp;

	temp = ft_strtrim(file, " "); 
	right_redirect(cmd, temp);
}

void singel_left_redirect(char *cmd, char *file)
{
	int fd;
	int pid;
	char *temp;

	if (!file)
		return ; // hata fırlatma kodu yaz
	else
	{
		temp = ft_strtrim(file, " ");
		fd = open(temp, O_RDONLY);
		if (fd < 0)
			exit(1);
		free(temp);
	}
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, STDIN_FILENO);
		close(fd);
		parse_string(cmd);
		exit(0);
	}
	wait(NULL);
	close(fd);
}
int find_char(char *str, int c)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			break;
		i++;
	}
	return (i);
}
char **redirect_delimiter(char *cmd)
{
	int i;
	int j;
	int len;
	int count;
	char **str;

	str = malloc(sizeof(char *) * red_count(cmd));
	i = 0;
	len = -1;
	count = -1;
	while (++len < red_count(cmd))
	{
		while(cmd[i] && (cmd[i] != '<' && cmd[i] != '>'))
			i++;
		j = i;
		while (cmd[j] && (cmd[j] == '>' || cmd[j] == '<'))
			j++;
		if (cmd[i] == '>' || cmd[i] == '<')
			str[++count] = ft_substr(cmd, i, j - i);
		i = j;
	}
	str[++count] = NULL;
	return (str);
}

int run(char **command, char **delimeter, ) // delimeter a göre yeniden çalıştır....
{
	int i;
	char **temp;

	i = 0;
	while (delimeter[i])
	{
		temp = split2(command[i], 32);
		if (temp[1])

	}
	return(0);
}

int redirect(char *cmd)
{
	char **tmp;
	char **a;
	int i;
	int j;

	tmp = redirect_split(cmd);
	a = redirect_delimiter(cmd);
	//tmp = join_redirect(tmp);
	i = 0;
	j = 0;
	while (tmp[i])
	{
		printf("%s\n", tmp[i++]);
		// if (cmd[i] == '>' && cmd[i + 1] == '>')
		// 	double_right_redirect(tmp[0], tmp[j++]);
		// else if (cmd[i] == '>')
		// 	single_right_redirect(tmp[0], tmp[j++]);
		// else if (cmd[i] == '<')
		// 	singel_left_redirect(tmp[0], tmp[j++]);
		// i++;
	}
	while (a[j])
		printf("%s\n", a[j++]);
	ft_free_double(tmp);
	return (0);
}

// int main()
// {
// 	char *i;
// 	i = readline("asdas : ");
// 	redirect(i);
// 	char **red;
// 	// red = split2(i, '>');

// 	// red = right_redirect(red);
// 	// int j = 0;
// 	// while (red[j])
// 	// 	printf("%s\n", red[j++]);
// }