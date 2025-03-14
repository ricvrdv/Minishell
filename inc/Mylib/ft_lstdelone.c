#include <stdlib.h>
#include "libft.h"

void    ft_lstdelone(t_list *lst, void(*del)(void *))
{
    if(!lst || !del)
        return ;
    if(lst)
    {
        del(lst->content);
        free(lst);
    }
}