#include "../include/minishell.h"

bool ft_is_valid_var_char(char c)
{
    // Valid variable name characters include letters, digits, and underscores.
    // The first character must not be a digit.
    if (ft_isalnum(c) || c == '_')
        return (true);
    return (false);
}

char    *ft_handle_dollar(char *args, int *i)
{
    int  start;
    char    *var_name;
    char    *var_val;

    (*i)++;
    if (args[*i] == '@' || ft_isdigit(args[*i]))
    {
        (*i)++;
        return (ft_strdup(""));
    }
    else if (args[*i] == '?')
    {
        (*i)++;
        return (ft_itoa(minishell.exit_status));
    }
    else if (!ft_is_valid_var_char(args[*i]))
    {
        //(*i)++;
        return (ft_strdup("$"));
    }
    start = *i;
    while (ft_is_valid_var_char(args[*i]))
        (*i)++;
    var_name = ft_substr(args, start, *i - start);
    var_val = ft_getenv_val(var_name);
    if (!var_val)
        return (free(var_name), ft_strdup(""));
    return (free(var_name), ft_strdup(var_val));
}

char	*ft_handle_squote(char *args, int *i)
{
	int	start;

	start = *i;
	(*i)++;
	while (args[*i] != '\'')
		(*i)++;
	(*i)++;
	return (ft_substr(args, start, *i - start));
}

char	*ft_handle_dquote_str(char *str, int *i)
{
	int	start;

	start = *i;
	while (str[*i] != '"' && str[*i] != '$')
	{
		(*i)++;
	}
	return (ft_substr(str, start, *i - start));
}

char	*ft_handle_dquote(char *args, int *i)
{
    char    *res;

    res = ft_strdup("\"");
    (*i)++;
	while (args[*i] != '"')
    {
        if (args[*i] == '$')
            res = ft_strjoin_free(res, ft_handle_dollar(args, i));
        else
            res = ft_strjoin_free(res, ft_handle_dquote_str(args, i));
    }
    (*i)++;
    //printf("je suis la\n");
	return (ft_strjoin_free(res, ft_strdup("\"")));
}