#include "../includes/bit.h"

void	complete_patch (char *patch, int *apatch_cursor)
{
	if ((*apatch_cursor + 1) % 8)
	{
		if (((*apatch_cursor) / 8) % 2)
		{
			while ((*apatch_cursor + 1) % 8)
				set0_bit (patch, (*apatch_cursor)++);
		}
		else
		{
			while ((*apatch_cursor + 1) % 8)
				set1_bit (patch, (*apatch_cursor)++);
		}
	}
	else if (((*apatch_cursor + 1) % 16 && find_bit (patch, *apatch_cursor)) ||
		(!(*apatch_cursor + 1) % 16 && !find_bit (patch, *apatch_cursor)))
	{
		while ((*apatch_cursor + 1) % 8)
			set0_bit (patch, (*apatch_cursor)++);
	}
}
