#include "vector.h"
#include <stdlib.h>
#include <string.h>

void	vec_init(t_vec *vec, int elem_size, void (*free_elem)(void *))
{
	vec->data = NULL;
	vec->size = 0;
	vec->capacity = 0;
	vec->elem_size = elem_size;
	vec->free_elem = free_elem;
}

static int	first_vec_alloc(t_vec *vec)
{
	vec->data = malloc(vec->elem_size * 8);
	if (!vec->data)
		return (-1);

	vec->capacity = 8;
	return (0);
}

int		vec_push(t_vec *vec, void *elem)
{
	if (vec->capacity == 0)
		if (first_vec_alloc(vec) == -1)
			return (-1);

	if (vec->size == vec->capacity)
	{
		void *new_data = realloc(vec->data, vec->capacity * 2 * vec->elem_size);
		if (!new_data)
			return (-1);
		vec->data = new_data;
		vec->capacity *= 2;
	}

	memcpy((char *)vec->data + vec->size * vec->elem_size, elem, vec->elem_size);
	vec->size++;
	return (0);
}

void	*vec_get(t_vec *vec, int index)
{
	if (index < 0 || index >= vec->size)
		return (NULL);
	return ((void *)((char *)vec->data + index * vec->elem_size));
}

void	vec_clear(t_vec *vec)
{
	int	i = 0;

	if (vec->free_elem)
	{
		while (i < vec->size)
		{
			vec->free_elem((char *)vec->data + i * vec->elem_size);
			i++;
		}
	}
	vec->size = 0;
}

void	vec_free(t_vec *vec)
{
	vec_clear(vec);
	free(vec->data);
	vec->data = NULL;
	vec->capacity = 0;
}
