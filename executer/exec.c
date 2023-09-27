#include "../include/minishell.h"





int ft_execute_node(t_node *node, bool piped)
{
    int exec_status;

    if (!node)
        return (1);
    if (node->type == N_PIPE)
        return (ft_execute-pipe(node));
    else if (node->type == N_AND)
    {
        exec_status = ft_execute_node(node->left, false);
        if (exec_status == SUCCESS)
            return (ft_execute_node(node->right, false));
        return (exec_status);
    }
    else if (node->type == N_OR)
    {
        exec_status = ft_execute_node(node->left, false);
        if (exec_status == SUCCESS)
           return (exec_status);
        return (ft_execute_node(node->right, false));
    }
    else
        return (ft_execute_scmd(node, false));
    return (GENERAL);
}

void    ft_start_execution(void)
{
   // signal(SIGQUIT, ft_signal_hanlder);
    ft_init_exec_tree(minishell.ast);
    if (minishell.heredoc_sigint)
    {
        //clear ast and reset heredoc_signint.
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &minishell.original_term);
    minishell.exit_status = ft_execute_node(minishell.ast, false);
    ft_clear_ast(minishell.ast);
}