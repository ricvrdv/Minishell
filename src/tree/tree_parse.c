#include "../../inc/minishell.h"

s_tree  *parse_pipe(s_token **tokens)  //global ptr to s_tokens [where we store our tokens]  in the following exemple : aaa | bbb 
{
    s_token *temp;                             
    s_token *next_token;
    s_tree  *pipe_node;

    temp = *tokens;                                                 //used to keep track of original position                     *aaa
    while(*tokens && (*tokens)->next)                               //while we check tokens 1 by 1    
    {
        next_token = (*tokens)->next;                               // = to the next token n+1                                      *|
        if((*tokens)->next->type == PIPE)                           //if we find token with pipe                                    on the exemple we do find it on first iteration
        {
            pipe_node = new_tree_node((*tokens)->next->type);            //allocate tree node and define type                        
            (*tokens)->next = NULL;                                 // our main ptr now only contain tokens before pipe             [aaa]
            pipe_node->left = parse_redirect(&temp);                     //left node tree =check for redirects if good exec cmd         execv[aaa] 
            pipe_node->right = parse_pipe(&(next_token->next));          //right node(recursion, break more the tree)if no other pipes go to parse redirect  
            free(next_token->value);                                
            free(next_token);
            return (pipe_node);                                          //return pipe node on s_tree 
        }
        *tokens = next_token;                                       //no pipe check next token
    }
    return (parse_redirect(&temp));                                 //to force right node to reach parse redirect  //on recursion *temp is refreshed
}

s_tree  *parse_redirect(s_token **tokens)   //used to check for redirects after checking pipes on left or right node
{
    s_token *temp;
    s_token *next_token;
    s_tree  *redirect_node;

    if(!*tokens)
        return (NULL);
    temp = *tokens;                                                             //used to keep track of original position
    if((*tokens)->type >= REDIRECT_L && (*tokens)->type <= HEREDOC)             //if our first token is redirect token     exemple : > echo "hello"
        return (create_redirection_node(tokens, temp));                         // we create a redirection node on our s_Tree
    while(*tokens && (*tokens)->next)                                           //while we check the tokens 1 by 1
    {
        next_token = (*tokens)->next;                                           //*next token
        if ((*tokens)->next->type >= REDIRECT_L && (*tokens)->next->type <= HEREDOC)        //we already checked first so we check next token
        {
            redirect_node = new_tree_node((*tokens)->next->type);               // Create a new tree node for the redirec assign type
            (*tokens)->next = next_token->next->next;                           // Skip the current redirection token and the next token (which is the argument)
            redirect_node->left = parse_redirect(&temp);                        // Recursively parse for any additional redirection tokens
            redirect_node->right = create_arg_node((next_token->next));         // Create a node for the argument associated with the redirection
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
    command_node->argcount = arg_count;
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