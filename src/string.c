static char tmpstr[17] = {0};


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

// itoa : int to char* using tmpstr / PopUp
char *itoa (int num)
{
	
	int i = 15;
	
	if (num < 0)
		tmpstr[0] = '-', num = num * -1;
	
	while (num > 0 && i >= 0)
	{
		
		tmpstr[i] = num % 10;
		num = (num - tmpstr[i]) / 10;
		
		tmpstr[i] = tmpstr[i] + 48; 
		
		i--;
		
	}
	
	if (tmpstr[0] == '-' && i >= 0)
		tmpstr[i] = '-', i--;
	
	return tmpstr+i+1;
		
}

