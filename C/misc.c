void MemoryMove(void *src, void *dst, int size)
{
	int i;

	if (dst == src)
	{
		return;
	}
	else if (dst < src)
	{
		for (i = 0; i < size; i++)
			dst[i] = src[i];
	}
	else // dst > src
	{
		for (i = size - 1; i >= 0; i--)
			dst[i] = src[i]
	}
}
	
