#include "../../../includes/my_lib.h"

int _is_space(int c)
{
    if(c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
        return (1);
    return (0);
}

int _is_directory(char *path)
{
    struct stat sb;

    if(stat(path, &sb) == 0 && S_ISDIR(sb.st_mode))
        return (1);
    return (0);
}
