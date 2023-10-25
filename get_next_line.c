/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-den <dvan-den@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:09:50 by dvan-den          #+#    #+#             */
/*   Updated: 2023/10/24 20:09:50 by dvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*extract_line(char	*processed_str)
{
	char	*line;
	int		i;

	i = 0;
	if (!processed_str[i])
		return (NULL);
	while (processed_str[i] != '\n' && processed_str[i])
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (processed_str[i] != '\n' && processed_str[i])
	{
		line[i] = processed_str[i];
		i++;
	}
	if (processed_str[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*get_processed_str(int fd, char *processed_str)
{
	char	*buffer;
	int		bytes_read;

	buffer = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	while (!ft_strchr(processed_str, '\n') && bytes_read != 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == -1)
			return (cleanup_and_return(NULL, buffer));
		buffer[bytes_read] = '\0';
		processed_str = ft_strjoin(processed_str, buffer);
	}
	return (cleanup_and_return(processed_str, buffer));
}

static char	*get_new_processed_str(char *processed_str)
{
	int		i;
	int		j;
	int		new_len;
	char	*new;

	if (!processed_str)
		return (NULL);
	i = 0;
	while (processed_str[i] != '\n' && processed_str[i])
		i++;
	if (!processed_str[i])
		return (cleanup_and_return(NULL, processed_str));
	new_len = ft_strlen(processed_str) - i;
	new = (char *)malloc(sizeof(char) * (new_len + 1));
	if (!new)
		return (NULL);
	j = 0;
	i++;
	while (processed_str[i])
		new[j++] = processed_str[i++];
	new[j] = '\0';
	return (cleanup_and_return(new, processed_str));
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*processed_str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	processed_str = get_processed_str(fd, processed_str);
	if (!processed_str)
		return (NULL);
	line = extract_line(processed_str);
	processed_str = get_new_processed_str(processed_str);
	return (line);
}
