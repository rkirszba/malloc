#include <stdio.h>
void			ft_memncpy(void *dest, const void *src, size_t n)
{
	size_t			i;

	i = 0;
	while (i < n)
	{
		((unsigned char*)dest)[i] = ((unsigned char*)src)[i];
		i++;
	}
}


int	main(void)
{
	int tab[5] = {1, 2, 3, 4, 5};
	int tab2[5];
	
	ft_memncpy(tab2, tab, 5 * sizeof(int));
	int i = 0;
	while (i < 5)
	{
		printf("%d\n", tab2[i]);
		i++;
	}
	return (0);
}
	
