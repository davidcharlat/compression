#include "../includes/bit.h"
#include "../includes/server.h"
#include "../includes/point_changes.h"
#include "../includes/patch.h"
#include <stdlib.h>

static void	file_patch (char *patch, char diff, int *apatch_cursor, int rank)
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
	i = 7;
	while (i >= 0)
	{
		if (1 & ((int)diff >> i))
			set1_bit (patch, (*apatch_cursor)++);
		else
			set0_bit (patch, (*apatch_cursor)++);
		i--;
	}
}

int			point_changes (char *buff_n, char *buff_n_1, char *patch)
{
	int		i;
	int		patch_cursor;
	char	diff;
	
	i = 0;
	patch_cursor = 3;
	set0_bit (patch, 0);
	set1_bit (patch, 1);
	set0_bit (patch, 2);
	while (i < BUFFER_SIZE)
	{
		if (diff = (buff_n[i] ^ buff_n_1[i]))
			file_patch (patch, diff, &patch_cursor, i);
		i++;
	}
	complete_patch (patch, &patch_cursor);
	return ((patch_cursor + 1) / 8);
}
