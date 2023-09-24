

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


//static t_env	*ft_envlst_new(char *key, char *value) __attribute__((unused));
void	ft_envlst_back(t_env *new);
void	ft_update_envlst(char *key, char *value, bool create);
char	*ft_extract_key(char *str);
char	*ft_extract_value(char *str);
void	ft_init_envlst(void);

//static void	ft_del(void *ptr);
void	*ft_garbage_collector(void *ptr, bool clean);
#endif