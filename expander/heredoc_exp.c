
#include "../include/minishell.h"

int ft_var_expander(char *line, int i, int fd)
{
    char    *exp_name;
    char    *exp_val;
    int    exp_debut;

    exp_debut = ++i;
    if (line[i] == '?')
    {
        ft_putnbr_fd(minishell.exit_status, fd);
        return (2);
    }
    while (line[i] && line[i] != '$' && line[i]  != ' ')
        i++;
    if (i != exp_debut)
    {
        exp_name = ft_garbage_collector(ft_substr(line, exp_debut, i), false);
        exp_val = ft_getenv_val(exp_name);
        if (exp_val)
            ft_putstr_fd(exp_val, fd);
    }
    return (i);
}

void    ft_heredoc_exp(char *line, int fd)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] == '$')
            i += ft_var_expander(line, i, fd);
        else
        {
            ft_putchar_fd(line[i], fd);
            i++;
        }
    }
    ft_putchar_fd('\n', fd);
}