/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaaltint@student.42istanbul.com.tr         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/08 22:33:35 by kaaltint          #+#    #+#             */
/*   Updated: 2026/09/08 22:35:23 by kaaltint         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_loop(int fd, char *stash, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(stash, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(stash);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (bytes_read > 0)
			stash = append_buffer(stash, buffer);
		if (!stash)
			return (NULL);
	}
	return (stash);
}

static char	*read_to_stash(int fd, char *stash)
{
	char	*buffer;

	if (!stash)
		stash = init_stash();
	if (!stash)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		free(stash);
		return (NULL);
	}
	stash = read_loop(fd, stash, buffer);
	free(buffer);
	return (stash);
}

static char	*extract_line(char *stash)
{
	char	*line;
	size_t	i;
	size_t	j;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

static char	*trim_stash(char *stash)
{
	char	*rest;
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i] || !stash[i + 1])
	{
		free(stash);
		return (NULL);
	}
	i++;
	rest = malloc(ft_strlen(stash + i) + 1);
	if (!rest)
	{
		free(stash);
		return (NULL);
	}
	j = 0;
	while (stash[i])
		rest[j++] = stash[i++];
	rest[j] = '\0';
	free(stash);
	return (rest);
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
	line = extract_line(stash);
	if (!line)
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	stash = trim_stash(stash);
	return (line);
}
