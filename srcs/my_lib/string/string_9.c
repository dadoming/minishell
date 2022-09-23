#include "../../../includes/my_lib.h"


char	_to_lower(char letter)
{
	if (letter >= 'A' && letter <= 'Z')
		letter += 32;
	return (letter);
}

char	_to_upper(char letter)
{
	if (letter >= 'a' && letter <= 'z')
		letter -= 32;
	return (letter);
}

char*	_trim(char const *s1, char const *set)
{
	char				*trim;
	unsigned int		i;
	unsigned int		len;

	if (!s1)
		return (0);
	if (!set)
		return (string()->_duplicate(s1));
	i = 0;
	while (s1[i] && string()->_search(set, s1[i]))
		i++;
	len = string()->_length((char *)s1 + i);
	while (len && (s1[len + i - 1] != 0) && string()->_search(set, s1[len + i - 1]))
		len--;
	trim = malloc(len + 1);
	if (!trim)
		return (0);
	string()->_copyl(trim, s1 + i, len + 1);
	trim[len] = '\0';
	return (trim);
}
