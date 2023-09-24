char    *ft_handle_normal(char *args, size_t *i)
{
    size_t  start;

    start = *i;
    while (args[*i] && args[*i] != '"' && args[*i] != '\''
        && args[*i] != '$')
        (*i)++;
    return (ft_substr(args, start, *i - start));
}

char    *ft_exp_cmd(char *args)
{
    char    exp_res;
    size_t      i;

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
    size_t                 i;

    args = ft_exp_cmd(args);
    if (!args)
        return (NULL);

    args = ft_clean_emptyargs(args);
    if (!args)
        return (NULL);
    
    expanded_args = ft_exp_split(args);
    free(args);
    if (!expanded_args)
        return (NUll);
    return (expanded_args);
}