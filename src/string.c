void * memcpy ( void * destination, const void * source, int num )
{
	int i;
	char *dest;
	char *src;
	dest = ((char*)destination);
	src = ((char*)source);
	if(dest > src)
	{
		for (i = num - 1; i >= 0; --i)
		{
			dest[i] = src[i];
		}		
	}
	else
	{
		for (i = 0; i < num; ++i)
		{
			dest[i] = src[i];
		}
	}
	return destination;
}
