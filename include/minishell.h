

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <unistd.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include "libft.h"
# include "tokenizer.h"
# include "parser.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef struct s_minishell
{
	char			*line;
	t_token			*tokens;
	t_token			*curr_token;
	t_node			*ast;
	int				exit_status;
	bool			signint_child;
	t_parse_err		parse_err;
	int				stdin;
	int				stdout;
	char			**environ;
	t_env			*envlst;
	bool			heredoc_sigint;
	struct termios	original_term;
}					t_minishell;

extern t_minishell	minishell;

//env
t_env	*ft_envlst_new(char *key, char *value) __attribute__((unused));
void	ft_envlst_back(t_env *new);
void	ft_update_envlst(char *key, char *value, bool create);
char	*ft_extract_key(char *str);
char	*ft_extract_value(char *str);
void	ft_init_envlst(void);
char	*ft_getenv_val(char *key);

//expansion
char **ft_expand(char *args);
char    *ft_exp_cmd(char *args);
char    *ft_handle_normal(char *args, int *i);
char	*ft_handle_dquote(char *args, int *i);
char	*ft_handle_dquote_str(char *str, int *i);
char	*ft_handle_squote(char *args, int *i);
char    *ft_handle_dollar(char *args, int *i);
bool ft_is_valid_var_char(char c);
void    ft_heredoc_exp(char *line, int fd);
int ft_var_expander(char *line, int i, int fd);
char    *ft_clean_empty_quotes(char *args);
char	**ft_args_split(char const *args);
char **ft_alloc_word(char const *args, char **strs);
void    ft_skip_word(char const *args, int *i);
char    **ft_fill_expanded_args(char const *args, char **exp_args);
void    fill_word(char const *args, char **exp_args, int *i, int j);

//execution
void    ft_start_execution(void);
void    ft_init_exec_tree(t_node *node);
void    ft_init_leaf_node(t_node *node);
bool ft_childproc_exit(int p[2], int *pid);
void    ft_heredoc_handler(t_io_node *io, int fd[2]);
bool	ft_is_limiter(char *limiter, char *line);
void	ft_del(void *ptr);
void	*ft_garbage_collector(void *ptr, bool clean);
#endif