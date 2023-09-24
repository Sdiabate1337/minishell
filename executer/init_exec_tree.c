
void    ft_heredoc_handler(t_io_node *io, int fd[2])
{
    char    *quote;
    char *line;

    quote = io->value;
    while (*quote && quote != '"' && *quote != '\'')
        quote++;
    while (1)
    {
        line = readline("heredoc> ");
        if (!line)
            break ;
        if (ft_is_limiter(io->value, line))
            break ;
        if (!*quote)
            ft_heredoc_exp(line, fd[1]);
        else
        {
            ft_putstr_fd(line, fd[1];
            ft_putstr_fd("\n", fd[1]));
        }
    }
}

bool ft_childproc_exit(int p[2], int *pid)
{
    waitpid(*pid, pid, 0);
    signal(SIGQUIT, ft_sigquit_handler);
    g_minishell.signint_child = false;
    close(p[1]);
    if (WIFEXITED(*pid) && WEXITSTATUS(*pid) == SIGINT)
        return (true);
    return (false);
}

void    ft_init_leaf_node(t_node *node)
{
    t_io_node   *io;
    int         fd[2];
    int       pid;

    if (node->args)
        node->expanded_args = ft_expand(node->args);
    io = node->io_list;
    while (io)
    {
        if (io->type == IO_HEREDOC)
        {
            pipe(fd);
            minishell.signint_child = true;
            pid = fork();
            if (!pid)
                ft_heredoc_handler(io, fd);
            if (ft_childproc_exit(fd, &pid))
                return ;
            io->heredoc = fd[0];
        }
        else
            io->expanded_value = ft_expand(io->value);
        io = io->next;
    }
}

void    ft_init_exec_tree(t_node *node)
{
    if (!node)
        return ;
    if (node->type == N_PIPE || node->type == N_AND
        || node->type == N_OR)
        {
            ft_init_exec_tree(node->left);
            if (!minishell.heredoc_sigint)
                ft_init_exec_tree(node->right);
        }
        else
            ft_init_leaf_node(node);
}