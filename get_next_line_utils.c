/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-den <dvan-den@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:09:55 by dvan-den          #+#    #+#             */
/*   Updated: 2023/10/25 05:12:59 by dvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*cleanup_and_return(char *value, char *buffer)
{
	free(buffer);
	return (value);
}

char	*ft_strchr(const char *s, int c)
{
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *processed_str, const char *buffer)
{
	int		str_len;
	int		buffer_len;
	char	*result;
	int		i;

	if (!processed_str)
		processed_str = "";
	if (!buffer)
		return (NULL);
	str_len = ft_strlen(processed_str);
	buffer_len = ft_strlen(buffer);
	result = (char *)malloc((str_len + buffer_len + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (++i < str_len)
		result[i] = processed_str[i];
	i = -1;
	while (++i < buffer_len)
		result[str_len + i] = buffer[i];
	result[str_len + buffer_len] = '\0';
	if (processed_str[0] != '\0')
		free((void *)processed_str);
	return (result);
}
