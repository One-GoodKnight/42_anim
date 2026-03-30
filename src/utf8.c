void	uchar_str_to_utf8(char *utf8, unsigned char *src)
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
