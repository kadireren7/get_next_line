/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaltint@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 19:07:07 by kaaltint          #+#    #+#             */
/*   Updated: 2026/11/19 19:35:30 by kaaltint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*append_chunk(char *stash, char *buffer)
{
	char	*new_stash;

	new_stash = gnl_join(stash, buffer);
	free(stash);
	return (new_stash);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;
	ssize_t	bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(stash), NULL);
	bytes = 1;
	while (!gnl_has_newline(stash) && bytes > 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes < 0)
			return (free(buffer), free(stash), NULL);
		buffer[bytes] = '\0';
		if (bytes > 0)
			stash = append_chunk(stash, buffer);
		if (!stash)
			break ;
	}
	free(buffer);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	stash = read_to_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = gnl_extract_line(stash);
	stash = gnl_clean_stash(stash);
	return (line);
}
