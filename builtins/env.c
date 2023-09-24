
#include "../include/minishell.h"


char	*ft_getenv_val(char *key)
{
	t_env	*env_lst;

	env_lst =  minishell.envlst;
	while (env_lst)
	{
		if (!ft_strcmp(key, env_lst->key))
			return env_lst->value;
		env_lst = env_lst->next;
	}
	return (NULL);
}

char	*ft_extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (ft_garbage_collector(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}

char	*ft_extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (ft_garbage_collector(
					ft_substr(str, i, ft_strlen(str) - i), false));
		}
		i++;
	}
	return (NULL);
}

void	ft_init_envlst(void)
{
	int		i;
	char	**environ;
	char	*key;
	char	*value;

	environ = minishell.environ;
	if (!environ)
		return ;
	i = 0;
	while (environ[i])
	{
		key = ft_extract_key(environ[i]);
		value = ft_extract_value(environ[i]);
		ft_update_envlst(key, value, true);
		i++;
	}
}