
int ft_in(t_io_node *io_node, int *status)
{
    int fd;

    // Check if expanded_value is NULL or has more than one element
    if (!io_node->expanded_value && io_node->expanded_value[1])
    {
         *status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_node->value});
         return (*status);
    }

    fd = open(io_node->expanded_value[0], O_RDONLY);
    if (fd == -1)
    {
        *status = ft_error_msg(ft_check_read(io_list->expanded_value[0]));
        return (*status);
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    *status = 0;
    return (*status);
}

int ft_out(t_node *node, int *status)
{
    int fd;

    if (!io_node->expanded_value && io_node->expanded_value[1])
    {
         *status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_node->value});
         return (*status);
    }
    fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        *status = ft_error_msg(ft_check_write(io_list->expanded_value[0]));
        return (*status);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    *status = 0;
    return (*status);
}

int ft_append(t_node *node, int *status)
{
    int fd;

    if (!io_node->expanded_value && io_node->expanded_value[1])
    {
         *status = ft_err_msg((t_err){ENO_GENERAL, ERRMSG_AMBIGUOUS, io_node->value});
         return (*status);
    }
    fd = open(io_list->expanded_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        *status = ft_error_msg(ft_check_write(io_list->expanded_value[0]));
        return (*status);
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    *status = 0;
    return (*status);
}