#include "utils/utils.h"
#include <stdlib.h>

void	free_array(void	**array)
{
	int	i;

	if (!array)
		return ;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}
