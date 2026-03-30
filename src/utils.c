#include "utils.h"

size_t	ft_strlen(const unsigned char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	uint_len(unsigned int n)
{
	int len;

	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	uint_str(unsigned char *dst, unsigned int n)
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

void	append_char(unsigned char *dst, unsigned char c)
{
	size_t	dst_len = ft_strlen(dst);
	dst[dst_len] = c;
	dst[dst_len + 1] = '\0';
}

int	ft_strncmp(const unsigned char *s1, const unsigned char *s2)
{
	size_t			i;

	if (n == 0)
		return (0);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
