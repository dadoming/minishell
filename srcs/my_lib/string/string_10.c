#include "../../../includes/my_lib.h"

char* _copy_until(char *str, int n)
{
    char    *dst;
    int     i;
    
    if (!str)
        return (NULL);
    i = 0;
    dst = malloc(sizeof(char) * (n + 1));
    while (n-- > 0)
    {
        dst[i] = str[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

int _array_length(char **array)
{
    int i;
    
    i = 0;
    while (array[i])
        i++;
    return (i);
}
