#include "gnl.h"
#include "read_file.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

unsigned char **get_lines_from_file()
{
	unsigned char	**lines;
	char	*line;
	size_t	count;

	int	fd = open(FILE_PATH);
	if (fd == -1)
		return (NULL);

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);

	lines = malloc(sizeof(unsigned char *) * (count + 1));
	if (!lines)
		return (NULL);

	int	fd = open(FILE_PATH);
	if (fd == -1)
	{
		free(lines);
		return (NULL);
	}
	
}
