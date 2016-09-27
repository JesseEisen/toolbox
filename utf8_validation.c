#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*To test char by this format 10xxxxxx*/
#define IS_CONT(b) (((unsigned char)(b) & 0xC0) == 0x80)

int bytes_in_sequence(unsigned char c)
{
	if(c == 0xC0 || c == 0xC1 || c > 0xF4 || IS_CONT(c))
	{
		return 0; /*not a valid code byte*/
	}
	else if((c & 0x80) == 0)    /*0xxxxxxx*/
	{
		return 1;
	}
	else if((c & 0xE0) == 0xC0) /*110xxxxx*/
	{
		return 2;
	}
	else if((c & 0xF0) == 0xE0) /*1110xxxx*/
	{
		return 3;
	}
	else if((c & 0xF8) == 0xF0) /*11110xxx*/
	{
		return 4;
	}

	return 0; /*never go here*/
}


int verify_utf8_sequence(const unsigned char *string, int *len)
{
	unsigned int cp = 0;
	*len = bytes_in_sequence(string[0]);

	/*remove code bit, recover the real number*/
	if(*len == 1)
	{
		cp = string[0];
	}
	else if(*len == 2 && IS_CONT(string[1]))
	{
		cp = string[0] & 0x1F;
		cp = (cp << 6) | (string[1] & 0x3F);
	}
	else if(*len == 3 && IS_CONT(string[1]) && IS_CONT(string[2]))
	{
		cp = (unsigned char)string[0] & 0xF;
		cp = (cp << 6) | (string[1] & 0x3F);
		cp = (cp << 6) | (string[2] & 0x3F);
	}
	else if(*len == 4 && IS_CONT(string[1]) && IS_CONT(string[2]) && IS_CONT(string[3]))
	{
		cp = string[0] & 0x7;
		cp = (cp << 6) | (string[1] & 0x3F);
		cp = (cp << 6) | (string[1] & 0x3F);
		cp = (cp << 6) | (string[1] & 0x3F);
	}
	else
	{
		return 0;
	}

	if((cp < 0x80     && *len > 1) ||
		(cp < 0x800   && *len > 2) ||
		(cp < 0x10000 && *len > 3))
	{
		return 0;
	}

	if(cp > 0x10FFFF)
	{
		return 0;
	}

	if(cp >= 0xD800 && cp <= 0xDFFF)
	{
		return 0;
	}

	return 1;
}


int is_valid_utf8(const char *string, size_t string_len)
{
	int len = 0;
	const char *string_end = string + string_len;
	while(string < string_end) 
	{
		if(!verify_utf8_sequence((const unsigned char *)string, &len))
		{
			return 0;
		}
		string += len;
	}

	return 1;
}


