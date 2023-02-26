#include "../../../includes/my_lib.h"

static char	*ft_strsearchr(char *s, int c);
static char	*read_file(int fd, char *text);
static char	*get_line(char *text);
static char	*extra_read(char *text);
static size_t	ft_strl(char *str);
static char	*ft_strjoiner(char *full_string, char *buff);

char	*get_next_line(int fd)
{
	static char		*text;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	text = read_file(fd, text);
	if (!text)
		return (0);
	line = get_line(text);
	text = extra_read(text);
	return (line);
}

static char	*read_file(int fd, char *text)
{
	char	*buff;
	int		read_count;

	buff = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (0);
	read_count = 1;
	while (!ft_strsearchr(text, '\n') && (read_count != 0))
	{
		read_count = read(fd, buff, BUFFER_SIZE);
		if (read_count == -1)
		{
			free (buff);
			return (0);
		}
		buff[read_count] = '\0';
		text = ft_strjoiner(text, buff);
	}
	free(buff);
	return (text);
}

char	*get_line(char *text)
{
	char	*line;
	int		i;

	i = 0;
	if (!text[i])
		return (0);
	while (text[i] != '\n' && text[i] != '\0')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (0);
	i = 0;
	while (text[i] != '\n' && text[i] != '\0')
	{
		line[i] = text[i];
		i++;
	}
	if (text[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*extra_read(char *text)
{
	int		i;
	int		j;
	char	*extra;

	i = 0;
	while (text[i] != '\0' && text[i] != '\n')
		i++;
	if (!text[i])
	{
		free(text);
		return (0);
	}
	extra = malloc(sizeof(char) * (ft_strl(text) - i + 1));
	if (!extra)
		return (0);
	j = 0;
	i++;
	while (text[i] != '\0')
	{
		extra[j++] = text[i++];
	}
	extra[j] = '\0';
	free(text);
	return (extra);
}



size_t	ft_strl(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoiner(char *full_string, char *buff)
{
	size_t		i;
	size_t		j;
	char		*str;

	if (!full_string)
	{
		full_string = malloc(sizeof(char));
		full_string[0] = '\0';
	}
	if (!full_string || !buff)
		return (0);
	j = 0;
	i = -1;
	str = malloc(sizeof(char) * (ft_strl(full_string) + ft_strl(buff) + 1));
	if (!str)
		return (0);
	while (full_string[++i] != '\0')
		str[i] = full_string[i];
	while (buff[j] != '\0')
	{
		str[i++] = buff[j++];
	}
	str[i] = '\0';
	free (full_string);
	return (str);
}

char	*ft_strsearchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != (unsigned char)c)
	{
		if (s[i] == '\0')
			return (NULL);
		i++;
	}
	return ((char *)&s[i]);
}
