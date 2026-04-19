#include "utils/utils.h"

size_t	uint_len(unsigned int n)
{
	size_t len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	uitoa(unsigned char *dst, unsigned int n)
{
	size_t	len;

	len = uint_len(n);
	dst[len] = '\0';
	while (len-- > 0)
	{
		dst[len] = (n % 10) + '0';
		n /= 10;
	}
}
