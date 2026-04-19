#include "gnl/gnl.h"
#include <unistd.h>
#include <stdlib.h>
#include <limits.h>

void	fill_stash(char *stash, char *buffer)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i])
		i++;
	while (buffer[i])
	{
		stash[j] = buffer[i];
		i++;
		j++;
	}
	stash[j] = '\0';
	return ;
}

char	*extract_line(char *str)
{
	char	*line;
	size_t	malloc_size;
	size_t	i;

	malloc_size = 0;
	while (str[malloc_size] && str[malloc_size] != '\n')
		malloc_size++;
	if (str[malloc_size] == '\n')
		malloc_size++;
	line = malloc(sizeof(char) * (malloc_size + 1));
	if (!line)
		return (free_s1_s2(str, NULL));
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	free(str);
	return (line);
}

char	fill_line(int fd, char **line, char *buffer)
{
	ssize_t		bytes_read;
	char		*temp;

	while (!ft_strchr(*line, '\n'))
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			return (1);
		if (bytes_read < 0)
		{
			free_s1_s2(*line, buffer);
			return (0);
		}
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(*line, buffer);
		if (!temp)
		{
			free_s1_s2(*line, buffer);
			return (0);
		}
		free(*line);
		*line = temp;
	}
	return (1);
}

char	*get_next_line(int fd)
{
	static char	stash[BUFFER_SIZE];
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > INT_MAX - 1)
	{
		stash[0] = '\0';
		return (NULL);
	}
	line = ft_strndup(stash, BUFFER_SIZE);
	if (!line)
		return (NULL);
	stash[0] = '\0';
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (free_s1_s2(line, NULL));
	if (!fill_line(fd, &line, buffer))
		return (NULL);
	free(buffer);
	fill_stash(stash, line);
	line = extract_line(line);
	if (ft_strlen(line) == 0)
		return (free_s1_s2(line, NULL));
	return (line);
}
