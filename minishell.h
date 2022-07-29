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
	void	*(*func_name)(t_cmd **, ...);
}	t_func;

typedef struct s_functions
{
	t_func	func;
	char	*arg;
}	t_functions;


void		loop();

void 		env(t_cmd **cmd);
void 		exit_f(t_cmd **cmd);
void		export(t_cmd **cmd);
void		unset(t_cmd **cmd);
void		ls(t_cmd **cmd);
void		cd(t_cmd **cmd);
void		pwd(t_cmd **cmd);
void		exit_f(t_cmd **cmd);
void		ft_grep(t_cmd **cmd);
void		ft_cat(t_cmd **cmd);
void		ft_wc(t_cmd **cmd);
void		ft_echo(t_cmd **cmd);


//-------------utils--------------//
void		multiple_waitpid(int *pid, int count);
void 		ft_multiple_close(int **fd, int len);
int			ft_fork(void);
int 		**ft_multiple_fd(int count);
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_read(int fd);
void		ft_pipe(char **cmd, int count);
void		ft_free_str(char **str);
char		*sequence(char *str);
char		**split2(char *str);
void		option(char **str, t_cmd *cmd);
void		arg(char **str, t_cmd *cmd);
int			ft_strstr(char *s1, char *s2);
char		*clear_quate(char *str);
int			quate_count(char *str);
int			first_index(char *str);
int			first_quate(char *str);
int			last_index(char *str);
int			find_char(char *str, char c);
void		print_all(char *str);

//-------------main process--------------//
void		parse_string(char *str);

#endif	