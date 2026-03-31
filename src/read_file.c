#include "gnl.h"
#include "read_file.h"
#include "data.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

ssize_t	count_lines()
{
	char	*line;
	size_t	count;

	int	fd = open(FILE_PATH, O_RDONLY);
	if (fd == -1)
		return (-1);

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
	return (count);
}

void	get_lines_from_file(t_data *data)
{
	unsigned char	**lines;
	unsigned char	*line;
	ssize_t	count;

	data->lines = NULL;
	data->count = 0;

	count = count_lines();
	if (count == -1)
		return ;

	lines = malloc(sizeof(unsigned char *) * (count + 1));
	if (!lines)
		return ;

	int	fd = open(FILE_PATH, O_RDONLY);
	if (fd == -1)
	{
		free(lines);
		return ;
	}
	
	int	i = 0;
	line = (unsigned char *)get_next_line(fd);
	while (line && i < count)
	{
		line[ft_strlen((char *)line) - 1] = 0;
		lines[i++] = line;
		line = (unsigned char *)get_next_line(fd);
	}
	free(line);
	lines[i] = NULL;
	close(fd);
	data->lines = lines;
	data->count = i;
}
