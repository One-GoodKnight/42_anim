#include "utils/utils.h"
#include "limits.h"

size_t	ft_strlen(const unsigned char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_strcmp(const unsigned char *s1, const unsigned char *s2)
{
	size_t			i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

bool ft_uatoi(const unsigned char *str, unsigned int *out)
{
	size_t	i;

	if (!str || !out)
		return (false);
	*out = 0;
	i = 0;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		if (*out > (UINT_MAX - (str[i] - '0')) / 10)
			return (false);
		*out = (*out * 10) + (str[i] - '0');
		i++;
	}
	if (str[i] != '\0')
		return (false);
	return (true);
}
