
#ifndef TOKENIZING_H
# define TOKENIZING_H

# define PROMPT "minishell$ "

typedef enum e_token_type
{
	T_IDENTIFIER,
	T_LESS,
	T_GREAT,
	T_DLESS,
	T_DGREAT,
	T_PIPE,
	T_O_PARENT,
	T_C_PARENT,
	T_AND,
	T_OR,
	T_NL,
}	t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

int	ft_append_separator(t_token_type type, char **line_ptr,
	t_token **token_list);
int	ft_append_identifier(char **line_ptr, t_token **token_list);
void	ft_clear_token_list(t_token **lst);
void	ft_token_list_add_back(t_token **lst, t_token *new_token);
t_token	*ft_new_token(char *value, t_token_type type);
t_token	*ft_tokenizer(char *line);
int	ft_handle_separator(char **line_ptr, t_token **token_list);
void	ft_print_quote_err(char c);
bool	ft_skip_quotes(char *line, size_t *i);
void	ft_skip_spaces(char **line);
int	ft_is_separator(char *s);
int	ft_is_quote(char c);
t_token	*ft_tokenize(void);

#endif