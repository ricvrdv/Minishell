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

void print_token_list(s_token *token_list)
{
    while (token_list)
    {
        if (token_list->value && *token_list->value)  
            printf("Token: [%s]\n", token_list->value);
        token_list = token_list->next;
    }
}

void ft_print_tree(s_tree *tree)
{

    // Print the type (you can customize this based on the actual types of s_type)
    printf("Tree node:\n");
    // Print the args (assuming it's a null-terminated array of strings)
    if (tree->args != NULL)
    {
        printf("  Args: ");
        for (int i = 0; tree->args[i] != NULL; i++)
            printf("'%s' ", tree->args[i]);
        printf("\n");
    }
    // Recursively print left and right subtrees if they exist
    if (tree->left != NULL)
    {
        printf("  Left subtree:\n");
        ft_print_tree(tree->left);
    }
    if (tree->right != NULL)
    {
        printf("  Right subtree:\n");
        ft_print_tree(tree->right);
    }
}