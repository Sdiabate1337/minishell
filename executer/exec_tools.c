
#include "../include/minishell.h"

void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*ft_garbage_collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}

bool	ft_is_limiter(char *limiter, char *line)
{
	while (*line)
	{
		if (*limiter == '"' || *limiter == '\'')
		{
			limiter++;
			continue ;
		}
		else if (*line == *limiter)
		{
			limiter++;
			line++;
		}
		else
			return (false);
	}
	while (*limiter == '"' || *limiter == '\'')
		limiter++;
	return (!*limiter);
}