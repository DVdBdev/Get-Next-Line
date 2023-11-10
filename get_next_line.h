/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-den <dvan-den@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 20:09:57 by dvan-den          #+#    #+#             */
/*   Updated: 2023/10/24 20:09:57 by dvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# define MAX_BUFFER_SIZE 4096

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 16
# else
#  if BUFFER_SIZE > MAX_BUFFER_SIZE
#   undef BUFFER_SIZE
#   define BUFFER_SIZE MAX_BUFFER_SIZE
#  endif
# endif

char	*get_next_line(int fd);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	*free_stash(char **stash, int create_line);

#endif