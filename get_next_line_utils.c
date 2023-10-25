/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-den <dvan-den@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:09:55 by dvan-den          #+#    #+#             */
/*   Updated: 2023/10/25 06:11:12 by dvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char	*cleanup_and_return(char *value, char *buffer)
{
	free(buffer);
	return (value);
}

char	*ft_strchr(char *s, int c)
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

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s, char *b)
{
	char	*result;
	int		i;
	int		j;

	if (!s)
	{
		s = (char *)malloc(sizeof(char));
		s[0] = '\0';
	}
	if (!b || !s)
		return (NULL);
	result = (char *)malloc((ft_strlen(s) + ft_strlen(b) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	j = 0;
	if (s)
		while (s[++i])
			result[i] = s[i];
	while (b[j])
		result[i++] = b[j++];
	result[ft_strlen(s) + ft_strlen(b)] = '\0';
	free(s);
	return (result);
}
