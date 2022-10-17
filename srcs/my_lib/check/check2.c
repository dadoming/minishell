#include "../../../includes/my_lib.h"

int _is_space(int c)
{
    if(c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r' || c == ' ')
        return (1);
    return (0);
}
