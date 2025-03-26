#include "../../inc/minishell.h"

void    init_struct(s_minishell *mini)
{
    char *curdir;

    mini->created = 1;
    curdir = get_dir(mini);
    mini->cur_dir = curdir;
    mini->full_cmd = NULL;
    mini->env = NULL;
    mini->tokens = NULL;
    mini->args = NULL;
    
}

void get_env(s_env **env_list, char **envp)
{
    char *sign;
    char *key;
    char *value;
    int i;

    *env_list = NULL; // Initialize the head of the linked list to NULL
    i = 0;
    while (envp[i])
    {
        sign = ft_strchr(envp[i], '=');
        if (sign)
        {
            key = ft_substr(envp[i], 0, (sign - envp[i])); // Extract the key
            value = ft_strdup(sign + 1); // Extract the value
            add_env_node(env_list, key, value); // Add the new node to the linked list
        }
        i++;
    }
}

s_env *create_original_env(char **envp)
{
    s_env *head;
    s_env *current;
    size_t key_length;
    s_env *new_node;
    char *sign; 
    char *key; 
    char *value;
    int i;

    i = 0;
    head = NULL;
    current = NULL;
    while (envp[i] != NULL) 
    {
        sign = strchr(envp[i], '='); 
        if (sign)
        {
            key_length = sign - envp[i]; 
            key = strndup(envp[i], key_length); 
            value = strdup(sign + 1);                               
            new_node = create_env_node(key, value); // Create a new environment variable node
            free(key); // Free the key after creating the node
            if (new_node == NULL) // Check if node creation was successful
                return NULL; // Or handle cleanup and return an error
            if (head == NULL)
                head = new_node; // Set head if it's the first node
            else
                current->next = new_node; // Link the new node
            current = new_node; // Move to the new node
        }
        i++; // Increment the index
    }
    return head; // Return the head of the linked list
}
