#include "../../inc/minishell.h"

s_tree  *parse_pipe(s_token **tokens)  // if first call parse_pipe to check if there are any tokens type pipe . if we dont find it we continue with parse_redirect
{
    s_token *temp;
    s_token *next_token;
    s_tree  *pipe;

    temp = *tokens;
    while(*tokens && (*tokens)->next)
    {
        next_token = (*tokens)->next;
        if((*tokens)->next->type == PIPE)   //FOUND A PIPE IN OUR CMD LIST
        {
            pipe = new_tree_node((*tokens)->next->type);    //allocate and define type
            (*tokens)->next = NULL;                         // break the str into left and right side
            pipe->left = parse_redirect(&temp);             //check for redirect if not parse cmd
            pipe->right = parse_pipe(&(next_token->next));      //starts after pipe token (right side), check again for pipe if pipe not found leaves and goes for parse redirect
            free(next_token->value);
            free(next_token);
            return (pipe);
        }
        *tokens = next_token;
    }
    return (parse_redirect(&temp));
}

s_tree  *parse_redirect(s_token **tokens)    //  will check for < << > >>
{
    s_token *temp;
    s_token *next_token;
    s_tree  *redirect_node;

    temp = *tokens;   //used to keep track of original position
    if((*tokens)->type >= REDIRECT_L && (*tokens)->type <= HEREDOC)  //if our first token is redirect token
        return (create_redirection_node(tokens, temp));    // we create a redirection node on our s_Tree
    while(*tokens && (*tokens)->next)
    {
        next_token = (*tokens)->next;                       //get next token
        if ((*tokens)->type >= REDIRECT_L && (*tokens)->type <= HEREDOC)
        {
            redirect_node = new_tree_node((*tokens)->next->type); // Create a new tree node for the redirection
            (*tokens)->next = next_token->next->next; // Skip the current redirection token and the next token (which is the argument)
            redirect_node->left = parse_redirect(&temp); // Recursively parse for any additional redirection tokens
            redirect_node->right = create_arg_node((next_token->next));  // Create a node for the argument associated with the redirection
            free(next_token->value);
            free(next_token);
            return (redirect_node);
        }
        *tokens = next_token; // Move to the next token
    }
    return (parse_command(&temp)); // If no redirection tokens are found, parse the command
}

s_tree  *parse_token(s_token **tokens)
{
    if(!tokens || !*tokens)
        return (NULL);
    return(parse_pipe(tokens));
}

s_tree	 *parse_command(s_token **tokens)
{
	s_tree		*command_node;
	int				arg_count;

	command_node = new_tree_node(WORD);
	arg_count = count_arguments(*tokens);
	command_node->args = safe_malloc(sizeof(char *) * (arg_count + 1));
	fill_command_arguments(command_node, tokens, arg_count);
	return (command_node);
}

int	count_arguments(s_token *current)
{
	int	arg_count;

	arg_count = 0;
	while (current && current->type == WORD)
	{
		arg_count++;
		current = current->next;
	}
	return (arg_count);
}

void	fill_command_arguments(s_tree *command_node,
	s_token **tokens, int arg_count)
{
	int		i;
	s_token	*tmp;

	i = 0;
	while (i < arg_count)
	{
		command_node->args[i] = ft_strdup((*tokens)->value);
		tmp = *tokens;
		*tokens = (*tokens)->next;
		free(tmp->value);
		free(tmp);
		i++;
	}
	command_node->args[arg_count] = NULL;
}