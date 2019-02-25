#include "../includes/bit.h"
#include "../includes/server.h"
#include "../includes/point_changes.h"
#include "../includes/patch.h"
#include <stdlib.h>

static void	file_patch_rank (char *patch, int *apatch_cursor, int rank)
{
	int	i;
	
	i = BUFFSIZE_BIT - 1;
	while (i >= 0 && *apatch_cursor < 8 * BUFFER_SIZE + 8)
	{
		if (1 & (rank >> i))
			set1_bit (patch, (*apatch_cursor)++);
		else
			set0_bit (patch, (*apatch_cursor)++);
		i--;
	}
}

static void	file_patch_diff (char diff[16], char *patch, int *apatch_cursor, int n)
{
	int	i;
	int	j;
	
	j = 0;
	while (j <= n)
	{
		i = 7;
		while (i >= 0)
		{
			set_bit (patch, (*apatch_cursor)++, 1 & ((int)(diff[j]) >> i));
			i--;
		}
		j++;
	}
}

static void	file_diff (char (*adiff)[16], char *buff_n, char *buff_n_1, int rank)
{
	int	i;
	
	i = 0;
	while (i < 16 && rank + i < BUFFER_SIZE)
	{
		(*adiff)[i] = (buff_n[rank + i] ^ buff_n_1[rank + i]);
		i++;
	}
}

static int	ptchanges_size_n (char *buff[2], char *patch, int n, int *apatch_cursor)
{
	int 	i;
	char	diff[16];
	
	i = 0;
	*apatch_cursor = 3;
	set0_bit (patch, 0);
	set1_bit (patch, 1);
	set1_bit (patch, 2);
	while (i < 4)
		set_bit (patch, (*apatch_cursor)++, 1 & (n >> 3 - i++));	
	i = 0;
	while (i < BUFFER_SIZE)
	{
		if (diff[0] = (buff[0][i] ^ buff[1][i]))
		{
			file_diff (&diff, buff[0], buff[1], i);
			file_patch_rank (patch, apatch_cursor, i);
			if (i + n >= BUFFER_SIZE)
				n = BUFFER_SIZE - i - 1;
			file_patch_diff (diff, patch, apatch_cursor, n);
			i += n;
		}
		i++;
	}
	complete_patch (patch, apatch_cursor);
	return ((*apatch_cursor + 1) / 8);
}

int			pointchanges_size (char *buff_n, char *buff_n_1, char *patch)
{
	int		i[2];
	int		size[2];
	int		memory;
	int		patch_cursor;
	char	*buff[2];
	
	memory = 15;
	buff[0] = buff_n;
	buff[1] = buff_n_1;
	size[0] = BUFFER_SIZE + 2;
	i[1] = 1;
	while (i[1] < 16)
	{
		size[1] = ptchanges_size_n (buff, patch, i[1], &patch_cursor);
		if (size[1] < size[0])
		{
			size[0] = size[1];
			memory = i[1];
		}
		i[1]++;
	}
	return (ptchanges_size_n (buff, patch, memory, &patch_cursor));
}
