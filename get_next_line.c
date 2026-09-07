#include "get_next_line.h"

static char	*init_stash(void)
{
	char	*stash;

	stash = malloc(1);
	if (!stash)
		return (NULL);
	stash[0] = '\0';
	return (stash);
}

static char	*append_buffer(char *stash, char *buffer)
{
	char	*new_stash;

	new_stash = ft_strjoin(stash, buffer);
	free(stash);
	return (new_stash);
}

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
