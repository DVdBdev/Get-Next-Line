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

/**
 * get_next_line - Read and extract the next line from 
 * 				   a file descriptor.
 *
 * @param fd: The file descriptor to read from.
 *
 * @return:
 * - On success: A dynamically allocated string containing 
 *               the next line from the file.
 * - When there are no more lines to read: NULL.
 * - On error: NULL (e.g., for invalid file descriptor or 
 *             memory allocation failure).
 *
 * Description:
 * The get_next_line function reads data from the file 
 * descriptor 'fd' and returns the next complete line. 
 * It uses a static string 'processed_str' to store and
 * manage leftover data between calls. The function extracts
 * lines from 'processed_str' one at a time and appends them 
 * to 'processed_str' after each read. This allows the function 
 * to work with data that might be fragmented across multiple reads.
 * The caller is responsible for freeing the dynamically allocated 
 * string returned by this function to prevent memory leaks.
 * 
 * credit comment block: 
 * Thank you for the explaination @chatgpt :)
 */
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
