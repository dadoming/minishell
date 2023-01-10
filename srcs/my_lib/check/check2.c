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

int _is_meta_char(char c)
{
    if (c == 46)// .
        return (1);
    if (c == 36)// $
        return (1);
    if (c == 42)// *
        return (1);
    if (c == 43)//+
        return (1);
    if (c == 63)// ?
        return (1);
    if (c == 124)// |
        return (1);
    if (c == 92)// "\\"
        return (1);
    if (c == 94)// ^
        return (1);
    if (c == 91)// [
        return (1);
    if (c == 123)//{
        return (1);
    if (c == 40)//(
        return (1);
    return (0);
}