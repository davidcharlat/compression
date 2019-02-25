#include "../includes/server.h"
#include "../includes/bit.h"
#include "../includes/patch.h"
#include <stdlib.h>

static int	check_diff (char *diff, int start, int end)
{
	while (start <= end)
	{
		if (find_bit (diff, start))
			return (1);
		start++;
	}
	return (0);
}	

static void	set_patch (char *diff, char *patch, int bound[2], int *apatch_cursor)
{
	int temp;
	
	if (bound[0] == bound[1] || *apatch_cursor > 8 * BUFFER_SIZE + 9)
		return;
	else if (bound[0] == bound[1] - 1)
	{
		if (find_bit (diff, bound[0]))
		{
			set1_bit (patch, *apatch_cursor);
			(*apatch_cursor)++;
		}
		else
		{
			set0_bit (patch, *apatch_cursor);
			(*apatch_cursor)++;
		}
	}
	else if (check_diff(diff, bound[0], bound[1]))
	{
		set1_bit (patch, *apatch_cursor);
		(*apatch_cursor)++;
		temp = bound [1];
		bound [1] = (bound[0] + bound[1]) / 2;
		set_patch (diff, patch, bound, apatch_cursor);
		bound [0] = bound[1];
		bound [1] = temp;
		set_patch (diff, patch, bound, apatch_cursor);
	}
	else
	{
		set0_bit (patch, *apatch_cursor);
		(*apatch_cursor)++;
	}
}

int			dichotom_1 (char *buff_n, char *buff_n_1, char *patch)
{
	char		*diff;
	int			i;
	int			bound[2] = {0};
	int			patch_cursor;
	
	i = 0;
	patch_cursor = 3;
	set0_bit (patch, 0);
	set0_bit (patch, 1);
	set1_bit (patch, 2);
	if (!(diff = (char*)malloc(2 * BUFFER_SIZE)))
		return (1073741823);
	while (i < BUFFER_SIZE)
	{
		diff[i] = buff_n[i] ^ buff_n_1[i];
		i++;
	}
	bound[1] = 8 * BUFFER_SIZE;
	set_patch (diff, patch, bound, &patch_cursor);
	complete_patch (patch, &patch_cursor);
	free (diff);
	return ((patch_cursor + 1) / 8);
}
