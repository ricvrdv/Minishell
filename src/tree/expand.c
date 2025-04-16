#include "../../inc/minishell.h"

void expand_tree(s_minishell *mini, s_tree *tree)
{
    int i;
    char *expansion;

    if(tree->type == WORD)
    {
        i = -1;
        while(tree->args[++i])
        {
            expansion = expand_variable(mini, tree->args[i]);
            free(tree->args[i]);
            tree->args[i] = expansion;
        }
    }
    if(tree->left)
        expand_tree(mini, tree->left);
    if(tree->right)
        expand_tree(mini, tree->right);
}


char *expand_variable(s_minishell *mini, const char *arg) 
{
    char *result;
    char var_name[256];
    const char *ptr;
    char *res_ptr;
    char *value; 

    result = safe_malloc(1024);
    ptr = arg;
    res_ptr = result;
    while (*ptr) 
    {
        if (*ptr == '$') 
        {
            get_variable_name(&ptr, var_name);                                                  // Extract variable name
            value = find_variable(mini, var_name);                                              // Find the variable's value
            append_value_to_result(&res_ptr, value);                                            // Append the value to the result
        } 
        else 
            *res_ptr++ = *ptr++;                                                                // Copy the character as is
    }
    *res_ptr = '\0';                                                                            // Null-terminate the result
    return result;                                                                              // Return the expanded command
}                                                         

void append_value_to_result(char **res_ptr, const char *value) 
{
    if (value) 
    {
        ft_strcpy(*res_ptr, value);                                                             // Copy the value into the result
        *res_ptr += ft_strlen(value);                                                           // Move the result pointer
    }
}

int get_variable_name(const char **ptr, char *var_name) 
{
    int i;

    i = 0;
    (*ptr)++;                                                                                   // Move past the '$'
    while (isalnum(**ptr) || **ptr == '_') 
    {
        var_name[i++] = **ptr;
        (*ptr)++;
    }
    var_name[i] = '\0';                                                                         // Null-terminate the variable name
    return i;                                                                                   // Return the length of the variable name
}

char *ft_strcpy(char *dest, const char *src) 
{
    char *original_dest;
    original_dest = dest;                               // Save the original pointer to the destination
    while (*src) 
    {
        *dest = *src;
        dest++;
        src++;
    }
    *dest = '\0';                                       // Null-terminate the destination string
    return original_dest;                               // Return the original destination pointer
}