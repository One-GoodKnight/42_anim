#ifndef VECTOR_H
# define VECTOR_H

typedef struct s_vec
{
    void    *data;
    int     size;
    int     capacity;
    int     elem_size;
    void    (*free_elem)(void *);
}   t_vec;

void	vec_init(t_vec *vec, int elem_size, void (*free_elem)(void *));
int		vec_push(t_vec *vec, void *elem);
void	*vec_get(t_vec *vec, int index);
void	vec_clear(t_vec *vec);
void	vec_free(t_vec *vec);

#endif
