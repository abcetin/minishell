#include "../minishell.h"

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
	char *ret;
	char *path;
	int i;

	path = getenv("PATH");
	temp = ft_split(path, ':');
	//free(path);
	i = -1;
	while (temp[++i])
	{
		if (find_path(temp[i], cmd))
		{
			ret = ft_strdup(temp[i]);
			ft_free_double((void **)temp);
			return (ret);
		}
	}
	ft_free_double((void **)temp);
	return(0);
}