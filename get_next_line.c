/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-den <dvan-den@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:09:50 by dvan-den          #+#    #+#             */
/*   Updated: 2023/11/10 10:35:32 by dvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// Copies the content of 'buffer' into 'stash'. 
// If 'stash' is NULL, duplicates 'buffer'.
// Frees the old 'stash' if it exists.
static char	*copy_to_stash(char *stash, char *buffer)
{
	char	*temp;
	char	*result;

	result = 0;
	if (!stash && buffer)
	{
		result = ft_strdup(buffer);
		if (!result)
			return (free_stash(&result, 0));
		return (result);
	}
	temp = ft_strdup(stash);
	if (!temp)
	{
		free_stash(&stash, 0);
		return (free_stash(&temp, 0));
	}
	free_stash(&stash, 0);
	result = ft_strjoin(temp, buffer);
	if (!result)
		free_stash(&result, 0);
	free_stash(&temp, 0);
	return (result);
}

// Checks if the given string 'stash' contains a newline character.
static int	has_newline(char *stash)
{
	size_t	i;

	if (!stash)
		return (0);
	i = 0;
	while (stash[i] != '\0')
	{
		if (stash[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

// Extracts a line from the 'stash' until the first newline character.
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

// Creates a new 'stash' by removing the first line (until the first newline).
static char	*remake_stash(char *stash)
{
	size_t	i;
	char	*result;

	i = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n')
		i++;
	if (stash[i + 1] == '\0')
		return (free_stash(&stash, 0));
	result = ft_substr(stash, i + 1, ft_strlen(stash));
	if (!result)
	{
		free_stash(&stash, 0);
		return (NULL);
	}
	free_stash(&stash, 0);
	return (result);
}

// Main function to read lines from a file descriptor 'fd'.
char	*get_next_line(int fd)
{
	char		buffer[BUFFER_SIZE + 1];
	long		bytes_read;
	static char	*stash = NULL;
	char		*line;

	line = 0;
	bytes_read = BUFFER_SIZE;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_stash(&stash, 0));
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if ((bytes_read <= 0 && !stash) || bytes_read == -1)
			return (free_stash(&stash, 0));
		buffer[bytes_read] = '\0';
		stash = copy_to_stash(stash, buffer);
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
