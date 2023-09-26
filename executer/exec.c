#include "../include/minishell.h"

void    ft_start_execution(void)
{
   // signal(SIGQUIT, ft_signal_hanlder);
    ft_init_exec_tree(minishell.ast);
    
}