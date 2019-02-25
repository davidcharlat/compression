	#include <stdio.h>

_Bool	find_bit (char *tab, int n)
{
	return ((_Bool)((tab[n / 8] << (n % 8)) & 128));
}

void	inv_bit (char *tab, int n)
{
	if (find_bit (tab, n))
		tab[n / 8] -= (128 >> (n % 8));
	else
		tab[n / 8] += (128 >> (n % 8));
}

void	set0_bit (char *tab, int n)
{
	if (find_bit (tab, n))
		tab[n / 8] -= (128 >> (n % 8));
}

void	set1_bit (char *tab, int n)
{
	if (!find_bit (tab, n))
		tab[n / 8] += (128 >> (n % 8));
}

void	set_bit (char *tab, int n, int val)
{
	if (val)
		set1_bit (tab, n);
	else
		set0_bit (tab, n);
}

int		bits_to_int (char *patch, int *apatch_cursor, int nb_of_bit)
{
	int	value;
	int	power;
	
	value = 0;
	power = 1 << (nb_of_bit - 1);
	while (power)
	{
		value += (int)(find_bit (patch, *apatch_cursor)) * power;
		power = power / 2;
		(*apatch_cursor)++;
	}
	return (value);	
}
