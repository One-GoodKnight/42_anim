#ifndef UTILS_H
# define UTILS_H

#include <stddef.h>

size_t	ft_strlen(const unsigned char *s);
void	append_char(unsigned char *dst, unsigned char c);
size_t	uint_len(unsigned int n);
void	uint_str(unsigned char *dst, unsigned int n);

#endif
