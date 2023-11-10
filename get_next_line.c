/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-den <dvan-den@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:09:50 by dvan-den          #+#    #+#             */
/*   Updated: 2023/11/10 10:27:13 by dvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*copy_to_stash(char *stash, char *buf)
{
	char	*temp;
	char	*res;

	res = 0;
	if (!stash && buf)
	{
		res = ft_strdup(buf);
		if (!res)
			return (free_stash(&res, 0));
		return (res);
	}
	temp = ft_strdup(stash);
	if (!temp)
	{
		free_stash(&stash, 0);
		return (free_stash(&temp, 0));
	}
	free_stash(&stash, 0);
	res = ft_strjoin(temp, buf);
	if (!res)
		free_stash(&res, 0);
	free_stash(&temp, 0);
	return (res);
}

static int	has_newline(char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	i = 0;
	if (!stash)
		return (free_stash(&stash, 0));
	while (stash[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (free_stash(&line, 0));
	j = 0;
	while (j < i + 1)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*remake_stash(char *stash)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n')
		i++;
	if (stash[i + 1] == '\0')
		return (free_stash(&stash, 0));
	res = ft_substr(stash, i + 1, ft_strlen(stash));
	if (!res)
	{
		free_stash(&stash, 0);
		return (NULL);
	}
	free_stash(&stash, 0);
	return (res);
}

char	*get_next_line(int fd)
{
	char		buf[BUFFER_SIZE + 1];
	long		ret;
	static char	*stash = NULL;
	char		*line;

	line = 0;
	ret = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_stash(&stash, 0));
	while (ret > 0)
	{
		ret = read(fd, buf, BUFFER_SIZE);
		if ((ret <= 0 && !stash) || ret == -1)
			return (free_stash(&stash, 0));
		buf[ret] = '\0';
		stash = copy_to_stash(stash, buf);
		if (has_newline(stash))
		{
			line = extract_line(stash);
			if (!line)
				return (free_stash(&stash, 0));
			return (stash = remake_stash(stash), line);
		}
	}
	return (free_stash(&stash, 1));
}
