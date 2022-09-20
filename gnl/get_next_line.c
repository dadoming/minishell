/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadoming <dadoming@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:47:33 by dadoming          #+#    #+#             */
/*   Updated: 2022/05/24 17:11:08 by dadoming         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_file(int fd, char *text)
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
