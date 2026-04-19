#ifndef UTILS_H
# define UTILS_H

#include <stddef.h>
#include <stdbool.h>

size_t	ft_strlen(const unsigned char *s);
void	append_char(unsigned char *dst, unsigned char c);
void	swap_uchar(unsigned char *u1, unsigned char *u2);
bool 	ft_uatoi(const unsigned char *str, unsigned int *out);

int		ft_strcmp(const unsigned char *s1, const unsigned char *s2);
int		ft_strcmp_ignore_case(const unsigned char *s1, const unsigned char *s2);

size_t	uint_len(unsigned int n);
void	uitoa(unsigned char *dst, unsigned int n);

void	free_array(void	**array);

#endif
