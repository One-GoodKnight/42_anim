#include "utils/utils.h"

void	append_char(unsigned char *dst, unsigned char c)
{
	size_t	dst_len = ft_strlen(dst);
	dst[dst_len] = c;
	dst[dst_len + 1] = '\0';
}

void	swap_uchar(unsigned char *u1, unsigned char *u2)
{
	unsigned char t = *u1;
	*u1 = *u2;
	*u2 = t;
}
