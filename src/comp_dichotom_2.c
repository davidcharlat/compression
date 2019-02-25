#include "../includes/server.h"
#include "../includes/bit.h"
#include "../includes/patch.h"
#include <stdlib.h>
	#include <stdio.h>

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

static int	file_1_and_diff_contens (char *diff, char *patch, int bound[2], int *apatch_cursor)
{
	int	 ret;
	
	ret = bound[1] - bound[0] + 1;
	set1_bit (patch, (*apatch_cursor)++);
	while (bound[0] < bound[1])
		set_bit (patch, (*apatch_cursor)++, find_bit(diff, bound[0]++));
	return (ret);	
}

static int	set_patch (char *diff, char *patch, int bound[2], int *apatch_cursor)
{
	int	temp;
	int	ret[2];
	int mem;
	
	mem = bound[0];
	if (bound[1] - bound[0] < 2)
		return (file_1_and_diff_contens (diff, patch, bound, apatch_cursor));
	if (!check_diff(diff, bound[0], bound[1] - 1))
	{
		set0_bit (patch, (*apatch_cursor)++);
		set0_bit (patch, (*apatch_cursor)++);
		return (2);
	}
	set0_bit (patch, (*apatch_cursor)++);
	set1_bit (patch, (*apatch_cursor)++);
	ret[0] = 1 + bound[1] - bound[0];
	temp = bound[1];
	bound[1] = (bound[0] + bound[1]) / 2;
	ret[1] = set_patch (diff, patch, bound, apatch_cursor);
	bound[0] = bound[1];
	bound[1] = temp;
	ret[1] += set_patch (diff, patch, bound, apatch_cursor) + 2;
	if (ret[1] >= ret[0])
	{
		(*apatch_cursor) -= (ret[1]);
		bound[0] = mem;
		return (file_1_and_diff_contens (diff, patch, bound, apatch_cursor));
	}
	return (ret[1]);                                   
}

int			dichotom_2 (char *buff_n, char *buff_n_1, char *patch)
{
	char		*diff;
	int			i;
	int			bound[2] = {0};
	int			patch_cursor;
	
	i = 0;
	patch_cursor = 3;
	set1_bit (patch, 0);
	set1_bit (patch, 1);
	set0_bit (patch, 2);
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
