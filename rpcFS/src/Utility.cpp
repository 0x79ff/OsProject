#include "Utility.h"

int Utility::Min(int a, int b)
{
    return (a<b)?a:b;
}

int Utility::StringLength(char *pString)
{
    int length = 0;
	char* pChar = pString;

	while( *pChar++ )
	{
		length++;
	}

	/* 返回字符串长度 */
	return length;
}

void Utility::StringCopy(char *src, char *dst)
{
	while ( (*dst++ = *src++) != 0 ) ;
}

void Utility::IOMove(unsigned char *from, unsigned char *to, int count)
{
    while(count--)
	{
		*to++ = *from++;//出现异常??
	}
	return;
}

/* 以 src 为源地址，dst 为目的地址，复制 count 个双字 */
void Utility::DWordCopy(int *src, int *dst, int count)
{
    while(count--)
	{
		*dst++ = *src++;
	}
	return;
}