#include "../include/minishell.h"

char    *ft_clean_empty_quotes(char *args)
{
    char    *char_t;
    int     i;
    int     j;
    int     len;
    char    *clean_args;

    if ((args[0] == '\'' && args[1] == '\'' && !args[2])
        || (args[0] == '"' && args[1] == '"' && !args[2]))
        return (args);
    char_t = ft_calloc(ft_strlen(args) + 1, sizeof(char));
    i = 0;
    j = 0;
    while (args[i])
    {
        if ((args[i] == '\'' && args[i + 1] == '\'') 
            || (args[i] == '"' && args[i + 1] == '"'))
            i += 2;
        else
            char_t[j++] = args[i++];
    }
    free(args);
    len = ft_strlen(char_t) + 1;
    clean_args = ft_calloc(len, sizeof(char));
    return (ft_strlcpy(clean_args, char_t, len), free(char_t), clean_args);
}

char    *ft_handle_normal(char *args, int*i)
{
    int start;

    start = *i;
    while (args[*i] && args[*i] != '"' && args[*i] != '\''
        && args[*i] != '$')
        (*i)++;
    return (ft_substr(args, start, *i - start));
}

char    *ft_exp_cmd(char *args)
{
    char    *exp_res;
    int    i;

    exp_res = ft_strdup("");
    i = 0;
    while (args[i])
    {
        if (args[i] == '\'')
            exp_res = ft_strjoin_free(exp_res, ft_handle_squote(args, &i));
        else if (args[i] == '"')
            exp_res = ft_strjoin_free(exp_res, ft_handle_dquote(args, &i));
        else if (args[i] == '$')
            exp_res = ft_strjoin_free(exp_res, ft_handle_dollar(args, &i));
        else
            exp_res =  ft_strjoin_free(exp_res, ft_handle_normal(args, &i));
    }
    return (exp_res);
}

char **ft_expand(char *args)
{
   char    **expanded_args;

    args = ft_exp_cmd(args);
    if (!args)
        return (NULL);
    args = ft_clean_empty_quotes(args);
    if (!args)
        return (NULL);
    expanded_args = ft_args_split(args);
    free(args);
    if (!expanded_args)
        return (NULL);
    return (expanded_args);
}