/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acetin <acetin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 10:12:14 by acetin            #+#    #+#             */
/*   Updated: 2022/09/10 11:27:53 by acetin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <dirent.h>
# include "./libft/libft.h"

extern char	**environ;

typedef struct s_cmd
{
	char	*cmd;
	t_list	*command;
}	t_cmd;

typedef struct s_func
{
	void	*(*func_name)(t_cmd);
}	t_func;

typedef struct s_functions
{
	t_func	func;
	char	*arg;
}	t_functions;

//-------------main process--------------//
void		loop(void);
//char		*rl_gets(char *str, const char *prompt);

//-------------built-in--------------//
void		env(t_cmd cmd);
void		exit_f(t_cmd cmd);
void		export(t_cmd cmd);
void		unset(t_cmd cmd);
void		cd(t_cmd cmd);
void		pwd(t_cmd cmd);
void		ft_echo(t_cmd cmd);
int			ft_execve(t_cmd cmd);

//-------------syntax_controls--------------//
int			check_syntax(char *str);
int			check_right_r(int pos, char *str);
int			check_right(int pos, char *str);
int			determine_syntax(char *str, int i);

//-------------utils--------------//
void		multiple_waitpid(int *pid, int count);
void		ft_multiple_close(int **fd, int len);
int			ft_fork(void);
int			**ft_multiple_fd(int count);
char		*ft_strjoin2(char *s1, char *s2);
void		ft_pipe(char **cmd, int count);
void		ft_free_double(char **pointer);
char		*sequence(char *str);
char		**split2(char *str, char c);
int			ft_strstr(char *s1, char *s2);
char		*clear_char(char *str, char c);
int			char_count(char *str, char c);
int			first_quote(char *str);
void		print_all(char *str, int quote);
void		set_funcs(t_functions *func);
void		get_func(t_cmd cmd);
int			dolar_sign(char *str);
int			quote_state(char *str, int pos);
int			word_count(char *str, char c);
void		parse_string(char *str);
char		*where(char *cmd);
void		ft_free_int(int **pointer, int count);
int			ft_strchr2(char *s, int c);
int			ft_double_strlen(char **str);
void		*ft_realloc(void *ptr, size_t size);
int			is_alnum(char *str);
int			exit_status(int status, int flag, char *message);
int			where_env(char *s2);
int			check_env_arg(t_cmd cmd);
void		free_env(char *arg);
void		add_env(char *env, int env_index);
void		with_pipe(char *str);

//------------------redirect-------------------//
int			redirect(char *cmd);
int			is_exist_file(char *path);
int			open_file(char *path);
void		clear_file(char *path);
int			red_count(char *str);
int			cut_red(char *dst, char **src);
char		**redirect_split(char *str);
char		**join_redirect(char **cmd);
char		**redirect_delimiter(char *cmd);
int			right_redirect(char *file);
int			single_right_redirect(char *file);
int			double_right_redirect(char *file);
int			singel_left_redirect(char *file);
int			double_left_redirect(char *eof);
void		run_heredoc(char **files, char **delimeter);

//-----------------------------------------------------//
void		add_to_list(char **temp, t_list **cmd);
int			lst_find(t_list **lst, void *data);
void		lstclear(t_list **lst);
#endif
