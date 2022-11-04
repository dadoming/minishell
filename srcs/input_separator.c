#include "../includes/minishell.h"

// echo "this and " that

int argcount(char *buffer)
{
    int count;
    int i;

    if(!buffer)
        return (0);
    i = 0;
    count = 0;
    while (buffer[i] != '\0')
    {
        // Check if word completes
        //      if yes count word
        //      if no then count word till delimiter and 
        //          start new count on delimiter until end of delimiter
        //          update index
        while 
        i++;
    }
    printf("%d\n", i);
    return (count);
}

char** split_args(char *buffer)
{
    //int i = 0;
    //char **ret;

    mini()->argc = argcount(buffer);
    printf("argc    %d\n", mini()->argc);
    return (0);
    //ret = malloc()
}