#include "../include/minishell.h"

void    fill_word(char const *args, char **exp_args, int *i, int j)
{
    char    quote;
    int         k;

    k = 0;
    while (args[*i] && args[*i] != ' ')
    {
        if (args[*i] != '\'' && args[*i] != '"')
            exp_args[j][k++] = args[(*i)++];
        else
        {
            quote = args[(*i)++];
            exp_args[j][k++] = quote;
            while (args[*i] != quote)
                exp_args[j][k++] = args[(*i)++];
            exp_args[j][k++] = args[(*i)++];
        }
    }
}

char    **ft_fill_expanded_args(char const *args, char **exp_args)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (args[i] && exp_args[j])
    {
        if (args[i] != ' ')
        {
            fill_word(args, exp_args, &i, j);
            j++;
        }
        while (args[i] == ' ')
            i++;
    }
    return (exp_args);
}

//skip word with quote as delimiter
void    ft_skip_word(char const *args, int *i)
{
    char    quote;

    while (args[*i] && args[*i] != ' ')
    {
        if (args[*i] != '\'' && args[*i] != '"')
            (*i)++;
        else
        {
            quote = args[(*i)++];
            while (args[(*i)] != quote)
                (*i)++;
            (*i)++;
        }
    }
}

char **ft_alloc_word(char const *args, char **strs)
{
    int start;
    int i;
    int j;

    i = 0;
    j = 0;
    while (args[i])
    {
        if (args[i] != ' ')
        {
            start = i;
            ft_skip_word(args, &i);
            strs[j] = ft_calloc(i - start + 1, sizeof(char));
            if (!strs[j])
                return (NULL);
            j++;
        }
        while (args[i] && args[i] == ' ')
            i++;
    }
    return (strs);
}

char	**ft_args_split(char const *args)
{
	int		count;
	char		**strs;
	char		**tofree;
	int		i;

	if (!args)
		return (NULL);
	i = 0;
	count = 0;
	while (args[i])
	{
		if (args[i] != ' ' && ++count)
			ft_skip_word(args, &i);
		while (args[i] && args[i] == ' ')
			i++;
	}
	strs = ft_calloc(count + 1, sizeof(char *));
	tofree = strs;
	strs = ft_alloc_word(args, strs);
	if (!strs || !count)
		return (ft_free_char2(tofree), NULL);
	return (ft_fill_expanded_args(args, strs));
}