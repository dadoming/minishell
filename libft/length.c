#include "../includes/my_lib.h"

unsigned int _length(const char *str)
{
    unsigned int i;
	
	i = 0;
    while (str[i] != '\0')
    {
        i++;
    }
    return (i);
}
