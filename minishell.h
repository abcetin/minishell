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
#include <dirent.h>
# include "./libft/libft.h"

extern char **environ;

typedef struct s_cmd
{
	char	*cmd;
	t_list	*command;
}	t_cmd;

// typedef struct s_cmd
// {
// 	char	*cmd;
// 	char	**option;
// 	char	**arg;
// 	char	**file;
// 	//int		error_status;
// }	t_cmd;

typedef struct s_func
{
	void	*(*func_name)(t_cmd *, ...);
}	t_func;

typedef struct s_functions
{
	t_func	func;
	char	*arg;
}	t_functions;

//-------------main process--------------//
void		loop();
//-------------built-in--------------//
void 		env(t_cmd *cmd);
void 		exit_f(t_cmd *cmd);
void		export(t_cmd *cmd);
//void		unset(t_cmd *cmd);
//void		ls(t_cmd **cmd);
void		cd(t_cmd *cmd);
void		pwd(t_cmd *cmd);
//void		ft_grep(t_cmd **cmd);
//void		ft_cat(t_cmd **cmd);
//void		ft_wc(t_cmd **cmd);
void		ft_echo(t_cmd *cmd);
int			ft_execve(t_cmd *cmd);

//-------------utils--------------//
void		multiple_waitpid(int *pid, int count);
void 		ft_multiple_close(int **fd, int len);
int			ft_fork(void);
int 		**ft_multiple_fd(int count);
char		*ft_strjoin2(char *s1, char *s2);
char		*ft_read(int fd);
void		ft_pipe(char **cmd, int count);
void		ft_free_double(void **pointer);
char		*sequence(char *str);
char		**split2(char *str, char c);
int			ft_strstr(char *s1, char *s2);
char		*clear_quote(char *str); // ft_strtrim kullan
int			char_count(char *str, char c);
//int			first_quote_index(char *str);
int			first_quote(char *str);
// int			last_quote_index(char *str);
void		print_all(char *str);
//int			ft_doublestrchr(char **str, char c);
int			ft_isspace(char str);
void		set_funcs(t_functions *func);
void		get_func(t_cmd *cmd);
int			dolar_sign(char *str);
int			quote_state(char *str, int pos);
int			word_count(char *str, char c);
//void		single_right_redirect(char *path);
void		parse_string(char *str);
int 		redirect(char *cmd);
char		*where(char *cmd);



//-----------------------------------------------------//
void	add_to_list(char **temp, t_list **cmd);
void	lst_find(t_list **lst, void *data);
void	lst_clear(t_list *lst);
#endif	