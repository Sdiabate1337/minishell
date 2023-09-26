
#include "../include/minishell.h"

void	ft_get_next_token(void)
{
	minishell.curr_token = minishell.curr_token -> next;
}

bool	ft_curr_token_is_binop(void)
{
	t_token_type	type;

	if (!minishell.curr_token)
		return (false);
	type = minishell.curr_token->type;
	if (type == T_PIPE || type == T_AND || type == T_OR)
		return (true);
	return (false);
}

int	ft_prec(t_token_type type)
{
	if (type == T_OR || type == T_AND)
		return (0);
	return (1);
}

int	ft_curr_token_prec(void)
{
	return (ft_prec(minishell.curr_token->type));
}

bool	ft_is_redir(t_token_type type)
{
	if (type == T_LESS || type == T_GREAT
		|| type == T_DLESS || type == T_DGREAT)
		return (true);
	return (false);
}