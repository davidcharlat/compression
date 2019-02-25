#include "../includes/bit.h"
#include "../includes/server.h"
#include "../includes/point_changes.h"
#include "../includes/patch.h"
#include <stdlib.h>

static void	file_patch_rank (char *patch, int *apatch_cursor, int rank)
{
	int	i;
	
	i = BUFFSIZE_BIT + 2;
	while (i >= 0 && *apatch_cursor < 8 * BUFFER_SIZE + 8)
	{
		set_bit (patch, (*apatch_cursor)++, (1 & (rank >> i)));
		i--;
	}
}

static void	file_patch_diff (char *diff, char *patch, int *apatch_cursor, int n, int diff_cursor)
{
	int	j;
	
	j = 0;
	while (j < n)
	{
		set_bit (patch, (*apatch_cursor)++, find_bit(diff, j + diff_cursor + 1));
		j++;
	}
}

static int	ptchanges_bit_n (char *diff, char *patch, int n, int *apatch_cursor)
{
	int 	i;
	
	i = 0;
	*apatch_cursor = 3;
	set1_bit (patch, 0);
	set0_bit (patch, 1);
	set1_bit (patch, 2);
	while (i < 8)
		set_bit (patch, (*apatch_cursor)++, 1 & (n >> 7 - i++));	
	i = 0;
	while (i < BUFFER_SIZE * 8)
	{
		if (find_bit(diff, i))
		{
			file_patch_rank (patch, apatch_cursor, i);
			if (i + n >= BUFFER_SIZE * 8)
				n = BUFFER_SIZE * 8 - i - 1;
			file_patch_diff (diff, patch, apatch_cursor, n, i);
			i += n;
		}
		i++;
	}
	complete_patch (patch, apatch_cursor);
	return ((*apatch_cursor + 1) / 8);
}

int			pointchanges_bit_size (char *buff_n, char *buff_n_1, char *patch)
{
	int		i[3] = {0};
	int		size[2];
	int		patch_cursor;
	char	*diff;
	
	if (!(diff = (char*)malloc(2 * BUFFER_SIZE)))
		return (1073741823);
	while (i[0] < BUFFER_SIZE)
	{
		diff[i[0]] = buff_n[i[0]] ^ buff_n_1[i[0]];
		(i[0])++;
	}
	size[0] = BUFFER_SIZE + 2;
	while (i[1] < 256)
	{
		size[1] = ptchanges_bit_n (diff, patch, i[1], &patch_cursor);
		if (size[1] < size[0])
		{
			size[0] = size[1];
			i[2] = i[1];
		}
		i[1]++;
	}
	return (ptchanges_bit_n (diff, patch, i[2], &patch_cursor));
}
