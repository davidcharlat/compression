#include "../includes/bit.h"
#include "../includes/server.h"
#include "../includes/point_changes.h"
#include "../includes/patch.h"
#include <stdlib.h>

/* 
** changes coded from the 4th to the penultimate bit
*/

static void	set_patch_cut_e (char *patch, char *diff, int start, int *apatch_cursor)
{
	int	i;
	
	i = 0;
	while (i <= start + 3)
	{
		set_bit (patch, *apatch_cursor, (int)find_bit (diff, i));
		i++;
		(*apatch_cursor)++;
	}
	if ((start % 8))
	{
			set0_bit (patch, (*apatch_cursor)++);
			set0_bit (patch, (*apatch_cursor)++);
			set0_bit (patch, (*apatch_cursor)++);
			set0_bit (patch, (*apatch_cursor)++);
	}
}

static void	set_patch_cut_b (char *patch, char *diff, int start, int *apatch_cursor)
{
	if (!(start % 8))
	{
		while (*apatch_cursor < 7)
			set0_bit (patch, (*apatch_cursor)++);
	}
	while (start < 8 * BUFFER_SIZE && *apatch_cursor < 8 * BUFFER_SIZE + 8)
	{
		set_bit (patch, *apatch_cursor, (int)find_bit (diff, start));
		start++;
		(*apatch_cursor)++;
	}
}

int			cut_end (char *buff_n, char *buff_n_1, char *patch)
{
	int		i;
	int		patch_cursor;
	char	*diff;
	
	i = BUFFER_SIZE;
	patch_cursor = 3;
	set1_bit (patch, 0);
	set0_bit (patch, 1);
	set0_bit (patch, 2);
	if (!(diff = (char*)malloc(2 * BUFFER_SIZE)))
		return (1073741823);
	while (i)
	{
		diff[i - 1] = buff_n[i - 1] ^ buff_n_1[i - 1];
		i--;
	}
	i = 8 * BUFFER_SIZE - 4;
	while (i >= 0)
	{
		if (find_bit (diff, i) || find_bit (diff, i + 1) 
			|| find_bit (diff, i + 2) || find_bit (diff, i + 3))
		{
			set_patch_cut_e (patch, diff, i, &patch_cursor);
			i = -8;
		}
		i -= 4;
	}
	while (i > -8)
	{
		set0_bit (patch, patch_cursor++);
		i--;
	}
	complete_patch (patch, &patch_cursor);
	free (diff);
	return ((patch_cursor + 1) / 8);
}

int			cut_beginning (char *buff_n, char *buff_n_1, char *patch)
{
	int		i;
	int		patch_cursor;
	char	*diff;
	
	i = BUFFER_SIZE;
	patch_cursor = 3;
	set0_bit (patch, 0);
	set0_bit (patch, 1);
	set0_bit (patch, 2);
	if (!(diff = (char*)malloc(2 * BUFFER_SIZE)))
		return (1073741823);
	while (i)
	{
		diff[i - 1] = buff_n[i - 1] ^ buff_n_1[i - 1];
		i--;
	}
	while (i < 8 * BUFFER_SIZE)
	{
		if (find_bit (diff, i) || find_bit (diff, i + 1) 
			|| find_bit (diff, i + 2) || find_bit (diff, i + 3))
		{
			set_patch_cut_b (patch, diff, i, &patch_cursor);
			i = 8 * BUFFER_SIZE;
		}
		i += 4;
	}
	while (i < 8 * BUFFER_SIZE + 4)
	{
		set0_bit (patch, patch_cursor++);
		i++;
	}
	complete_patch (patch, &patch_cursor);
	free (diff);
	return ((patch_cursor + 1) / 8);
}
