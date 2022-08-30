#include "../minishell.h"
#include <string.h>
int find_path(char *path, char *cmd)
{
	struct dirent *de;
	DIR *dir;

	dir = opendir(path);
	if (dir == NULL)
	{
		printf("Could not open current directory");
		return (0);
	}
	while ((de = readdir(dir)))
	{
		if (ft_strstr(de->d_name, cmd))
			return (1);
	}
	closedir(dir);
	return (0);
}

char *where(char *cmd)
{
	char **temp;
	//char *command;
	char *ret;
	int i;

	temp = ft_split(getenv("PATH"), ':');
	i = -1;
	while (temp[++i])
	{
		if (find_path(temp[i], cmd))
		{
			ret = strdup(temp[i]);
			ft_free_double(temp);
			return (ret);
		}
	}
	ft_free_double(temp);
	//free(cmd);
	return(NULL);
}