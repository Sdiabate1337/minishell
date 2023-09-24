#include "../include/minishell.h"

t_minishell minishell;

const char *node_type_strings[] = {
    "N_PIPE",
	"N_AND",
	"N_OR",
	"N_CMD"  
};

const char *io_type_strings[] = {
    "IO_IN",
	"IO_OUT",
	"IO_HEREDOC",
	"IO_APPEND"
};

void print_io_node(t_io_node *io_node)
{
    if (io_node)
    {
        if (io_node->type >= IO_IN && io_node->type <= IO_APPEND)
        {
            printf("io Type: %s\n", io_type_strings[io_node->type]);
        }
        else
        {
            printf("io Type: Unknown\n");
        }
        printf("IO Value: %s\n", io_node->value);
        // You can also print other information related to the IO node if needed.
        // Recursively print the next IO node.
        print_io_node(io_node->next);
    }
}

void print_node(t_node *node)
{
    if (node)
    {
        if (node->type >= N_PIPE && node->type <= N_CMD)
        {
            printf("node Type: %s\n", node_type_strings[node->type]);
        }
        else
        {
            printf("node Type: Unknown\n");
        }
        printf("Node Args: %s\n", node->args);
        printf("Node Expanded Args: %s\n", node->expanded_args ? node->expanded_args[0] : "(null)");
        
        // Print the IO nodes associated with this node.
        printf("IO List for this Node:\n");
        print_io_node(node->io_list);

        // Recursively print the left and right subtrees.
        if (node->left)
        {
            printf("Left Subtree:\n");
            print_node(node->left);
        }
        if (node->right)
        {
            printf("Right Subtree:\n");
            print_node(node->right);
        }
    }
}

// Function to print the entire AST starting from the root node.
void print_ast(t_node *root)
{
    if (root)
    {
        printf("AST Root Node:\n");
        print_node(root);
    }
}

const char *token_type_strings[] = {
    "T_IDENTIFIER",
    "T_LESS",
    "T_GREAT",
    "T_DLESS",
    "T_DGREAT",
    "T_PIPE",
    "T_O_PARENT",
    "T_C_PARENT",
    "T_AND",
    "T_OR",
    "T_NL"
};

void print_tokens(t_token *token_list)
{
    // Iterate through the token list
    while (token_list != NULL)
    {
        // Check if the token type is within the valid range
        if (token_list->type >= T_IDENTIFIER && token_list->type <= T_NL)
        {
            printf("Token Type: %s\n", token_type_strings[token_list->type]);
        }
        else
        {
            printf("Token Type: Unknown\n");
        }

        printf("Token Value: %s\n", token_list->value);

        // Move to the next token
        token_list = token_list->next;
    }
}






static void	ft_init_minishell(char **env)
{
	ft_memset(&minishell, 0, sizeof(t_minishell));
	minishell.environ = env;
	ft_init_envlst();
	minishell.stdin = dup(0);
	minishell.stdout = dup(1);
	tcgetattr(STDIN_FILENO, &minishell.original_term);
}

int	main(int argc, char **argv, char **env)
{
	((void)argc, (void)argv);
	ft_init_minishell(env);
	while (1)
	{
		//ft_init_signals();
		minishell.line = readline(PROMPT);
	/*
        	if (!minishell.line)
			(ft_clean_ms(),
				ft_putstr_fd("exit\n", 1), exit(minishell.exit_s));
		if (minishell.line[0])
			add_history(minishell.line);
    */
		minishell.tokens = ft_tokenize();
        //print_tokens(minishell.tokens);
		if (!minishell.tokens)
			continue ;
		minishell.ast = ft_parse();
        print_ast(minishell.ast);
		/*
            if (minishell.parse_err.type)
		{
			ft_handle_parse_err();
			continue ;
		}
        */
		//ft_start_execution();
	}
	ft_garbage_collector(NULL, true);
    return (0);
	//return (ft_clean_ms(), minishell.exit_s);
}