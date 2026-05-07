#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>

size_t	ft_signed_strlen(const char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*free_s1_s2(char *s1, char *s2)
{
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (NULL);
}

char	*ft_strndup(const char *s, size_t n)
{
	char		*dup;
	size_t		s_len;
	size_t		i;

	if (!s)
		return (NULL);
	s_len = ft_signed_strlen(s);
	if (s_len < n)
		dup = malloc(sizeof(char) * (s_len + 1));
	else
		dup = malloc(sizeof(char) * n + 1);
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (i < s_len && i < n)
	{
		dup[i] = s[i];
		i++;
	}
	if (i < n)
		dup[i] = '\0';
	return (dup);
}

char	*ft_strchr(const char *s, int c)
{
	int				i;
	char			*s_char;
	unsigned char	c_char;

	if (!s)
		return (NULL);
	i = 0;
	s_char = (char *)s;
	c_char = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == c_char)
			return (&s_char[i]);
		i++;
	}
	if (s[i] == c_char)
		return (&s_char[i]);
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*join;
	size_t	i;

	s1_len = ft_signed_strlen(s1);
	s2_len = ft_signed_strlen(s2);
	join = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (join == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len)
	{
		join[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < s2_len)
	{
		join[s1_len + i] = s2[i];
		i++;
	}
	join[s1_len + s2_len] = '\0';
	return (join);
}
