
int ft_check_io(t_node *node)
{
    t_io_node   *pseudo_io;
    int         pseudo_status;

    pseudo_io = node->io_list;
    while (pseudo_io)
    {
        if (pseudo_io->type == IO_IN)
        {
            if (ft_in(pseudo_io, &pseudo_status) != SUCCESS)
                return (pseudo_status);
        }
        else if (pseudo_io->type == IO_OUT)
        {
             if (ft_out(pseudo_io, &pseudo_status) != SUCCESS)
                return (pseudo_status);
        }
       `else if (pseudo_io->type == IO_APPEND)
        {
             if (ft_append(pseudo_io, &pseudo_status) != SUCCESS)
                return (pseudo_status);
        }
        else if (pseudo_io->type == IO_HEREDOC)
        {
            dup2(pseudo_io->here_doc, 0);
            close(pseudo_io->here_doc);
        }
        pseudo_io = pseudo_io->next;
    }
    return (SUCCESS);
}

int ft_execute_scmd(t_node *node, int piped)
{
    if (!node->expanded_args)
    {
        pseudo_status = ft_check_io(node);
        ft_reset_stds(piped);
        return (pseudo_status && GENERAL);
    }
    else if (ft_isbuiltin_cmd(node->expanded_args[0]))
    {
        pseudo_status = ft_check_io(node);
        if (pseudo_status != SUCCESS)
            return (ft_reset_stds(piped), GENERAL);
        pseudo_status = ft_exec_builtin(node->expanded_args);
        return (ft_reset_stds(piped), pseudo_status);
    }
    else
        return (ft_exec_child(node));
}