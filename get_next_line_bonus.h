/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dvan-den <dvan-den@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 09:09:40 by dvan-den          #+#    #+#             */
/*   Updated: 2023/11/14 09:17:01 by dvan-den         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
char	*ft_strdup_bonus(const char *s1);
char	*ft_strjoin_bonus(char const *s1, char const *s2);
char	*ft_substr_bonus(char const *s, unsigned int start, size_t len);
void	*free_stash_bonus(char **stash, int create_line);

#endif