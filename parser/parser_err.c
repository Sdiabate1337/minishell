#include "../include/minishell.h"

void	ft_set_parse_err(t_parse_err_type type)
{
	minishell.parse_err.type = type;
}