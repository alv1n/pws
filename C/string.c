#include "string.h"
#include "asm.h"

int StringCompare2(const char *s1, const char *s2)
{
	while (*s1 == *s2)
	{
		if (*s1 == '\0')
		{
			return 0;
		}
		s1++;
		s2++;
	}
	return (int) s1 - (int) s2;
}

int StringLength(const char *s)
{
	return CharCount(s);
}
