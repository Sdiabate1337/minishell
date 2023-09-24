#include "../include/minishell.h"

t_token	*ft_tokenize(void)
{
	char	*line;
	t_token	*token_list;

	line = minishell.line;
	token_list = ft_tokenizer(line);
	free(line);
	minishell.line = NULL;
	return (token_list);
}