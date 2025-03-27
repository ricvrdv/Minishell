#include "../../inc/minishell.h"


const char *token_name(s_type type)
{
    const char  *token_type[7];

    token_type[0] = "WORD";
    token_type[1] = "PIPE";
    token_type[2] = "REDIRECT_L";
    token_type[3] = "REDIRECT_R";
    token_type[4] = "APPEND";
    token_type[5] = "HEREDOC";
    token_type[6] = "TOKEN";
    if(type >= 0 && type < 7)
        return (token_type[type]);
    return ("DUNNO");
}

void print_token(s_token *tokens)
{
    s_token *token;
    int i = 1;

    token = tokens;
    while(token)
    {
        printf("Token %i: %s\n",i ,token->value);
        printf("Type: %s\n", token_name(token->type));
		printf("--------------------------------------------------\n");
 		token = token->next;
        i++;
    }
}

void ft_print_tree(s_tree *tree, int depth) 
{

    if (tree == NULL) 
        return; // Base case: if the tree is empty, do nothing
    // Print the current node's type with indentation based on depth
    for (int i = 0; i < depth; i++) 
        printf("  "); // Indentation for depth
    // Print the type of the node based on the s_type enumeration
    switch (tree->type) {
        case WORD:
            printf("Word Node:\n");
            break;
        case PIPE:
            printf("Pipe Node:\n");
            break;
        case REDIRECT_L:
            printf("Redirect In Node:\n");
            break;
        case REDIRECT_R:
            printf("Redirect Out Node:\n");
            break;
        case APPEND:
            printf("Append Node:\n");
            break;
        case HEREDOC:
            printf("Here Document Node:\n");
            break;
        case TOKEN:
            printf("Token Node:\n");
            break;
        default:
            printf("Unknown Node Type:\n");
            break;
    }
    // Print the file type if applicable (for redirection nodes)
    if (tree->type == REDIRECT_L || tree->type == REDIRECT_R || tree->type == APPEND) 
        printf("  File Type: %d\n", tree->file_type); // Print file type for relevant nodes
    // Print the args (assuming it's a null-terminated array of strings)
    if (tree->args != NULL) {
        for (int i = 0; tree->args[i] != NULL; i++) 
        {
            for (int j = 0; j < depth + 1; j++) 
                printf("  "); // Indentation for args
            printf("Arg: '%s'\n", tree->args[i]);
        }
    }
    // Recursively print left and right subtrees if they exist
    if (tree->left != NULL) 
        ft_print_tree(tree->left, depth + 1); // Increase depth for left subtree
    if (tree->right != NULL) 
        ft_print_tree(tree->right, depth + 1); // Increase depth for right subtree
    
}