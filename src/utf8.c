#include <stddef.h>

void	latin1_to_utf8(unsigned char *utf8, unsigned char *src)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (src[i])
	{
		if (src[i] < 0b10000000) 	//plain ascii
			utf8[j++] = src[i];
		else						//two bytes ascii
		{
			// 0b is for binary
			// first par of each byte is the number of bytes remaining for the current character
			utf8[j++] = 0b11000000 | (src[i] >> 6); //keep only 2 bits because 6 are reserved from the line under
			utf8[j++] = 0b10000000 | ((0b00111111) & src[i]); //get the remaining 6 bits of the uchar
		}
		i++;
	}
	utf8[j] = '\0';
}

size_t	count_leading_bits(char byte)
{
	size_t	count = 0;

	while (count < 8 && (byte & 0b10000000))
	{
		byte <<= 1;
		count++;
	}
	return (count);
}

void	utf8_to_latin1(unsigned char *dest, unsigned char *utf8)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while(utf8[j])
	{
		if (utf8[j] >= 0b11100000)
		{
			j += count_leading_bits(utf8[j]);
			continue ;
		}
		if (utf8[j] < 0b10000000)
			dest[i++] = utf8[j++];
		else
		{
			unsigned char	n = 0;
			n |= (0b00000011 & utf8[j++]) << 6;
			n |= (0b00111111 & utf8[j++]);
			dest[i++] = n;
		}
	}
	dest[i] = '\0';
}
