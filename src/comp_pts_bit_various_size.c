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

static void	file_difference (char *diff, int *adiff_cursor, char *patch, int *apatch_cursor)
{
	int	nb_of_0;
	int	lenght;
	int	mem_patch_cursor;
	
	mem_patch_cursor = *apatch_cursor;
	nb_of_0 = 0;
	*apatch_cursor += (BUFFSIZE_BIT + 3);
	file_patch_rank (patch, apatch_cursor, *adiff_cursor);
	(*adiff_cursor)++;
	while (nb_of_0 < 2 * BUFFSIZE_BIT + 4 && *adiff_cursor < 8 * BUFFER_SIZE)
	{
		if (find_bit(diff, *adiff_cursor))
			nb_of_0 = 0;
		else
			nb_of_0++;
		set_bit (patch, (*apatch_cursor)++, find_bit(diff, (*adiff_cursor)++));
	}
	*apatch_cursor -= nb_of_0;
	lenght = *apatch_cursor - mem_patch_cursor - 2 * BUFFSIZE_BIT - 5;
	file_patch_rank (patch, &mem_patch_cursor, lenght);
	if (lenght > 1)
		(*apatch_cursor)--;
}

static void	file_patch (char *diff, char *patch, int *apatch_cursor)
{
	int	diff_cursor;
	
	diff_cursor = 0;
	while (diff_cursor < BUFFER_SIZE * 8)
	{
		if (find_bit(diff, diff_cursor))
			file_difference (diff, &diff_cursor, patch, apatch_cursor);
		diff_cursor++;
	}
}

int			pts_bit_various_size (char *buff_n, char *buff_n_1, char *patch)
{
	int		i;
	int		patch_cursor;
	char	*diff;
	
	i = 0;
	if (!(diff = (char*)malloc(2 * BUFFER_SIZE)))
		return (1073741823);
	while (i < BUFFER_SIZE)
	{
		diff[i] = buff_n[i] ^ buff_n_1[i];
		(i)++;
	}
	set1_bit (patch, 0);
	set1_bit (patch, 1);
	set1_bit (patch, 2);
	set0_bit (patch, 3);
	patch_cursor = 4;
	file_patch (diff, patch, &patch_cursor);
	complete_patch (patch, &patch_cursor);
	free (diff);
	return ((patch_cursor + 1) / 8);
}
