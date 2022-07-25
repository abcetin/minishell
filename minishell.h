#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>
# include <signal.h>
# include <sys/wait.h>
# include <fcntl.h>
# include "./libft/libft.h"

extern char **environ;

typedef struct s_cmd
{
	char	*cmd;
	char	**option;
	char	**arg;
}	t_cmd;

typedef struct s_func
{
	void	*(*func_name)(char ** , ...);
}	t_func;

typedef struct s_functions
{
	t_func	func;
	char	*arg;
}	t_functions;

void 		env(char **cmd);
void 		exit_f(char **cmd);
int			ft_strstr(char *s1, char *s2);
void		export(char **cmd);
void    	unset(char **cmd);
void    	ls(char **cmd);
char    	*ft_strjoin2(char *s1, char *s2);
void		*ft_realloc(void *ptr, unsigned int new_size);
void		ft_grep(char **cmd);
char		*ft_read(int fd);
void		ft_cat(char **cmd);
void		parse_string(char *str);
void		ft_wc(char **cmd);
void		ft_pipe(char **cmd, int count);
void		multiple_waitpid(int *pid, int count);
void 		ft_multiple_close(int **fd, int len);
int			ft_fork(void);
int 		**ft_multiple_fd(int count);
void    	ft_echo(char **cmd);
t_cmd		*parse_cmd(char **cmd);
void		ft_free_str(char **str);
#endif	