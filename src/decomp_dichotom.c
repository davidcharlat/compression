#include "../includes/bit.h"
#include "../includes/server.h"
#include "../includes/decompress.h"
#include "../includes/point_changes.h"
#include <stdlib.h>

static void	file_part_of_newpatch_dichotom (char *patch, int *cursor, char (*anew_patch)[BUFFER_SIZE], int bound[2])
{
	int	temp[2];
	
	if (find_bit (patch, *cursor) && bound[1] > bound[0] + 1)
	{
		(*cursor)++;
		temp[0] = bound[0];
		temp[1] = (bound[1] + bound[0]) / 2;
		file_part_of_newpatch_dichotom (patch, cursor, anew_patch, temp);
		temp[0] = temp[1];
		temp[1] = bound[1];
		file_part_of_newpatch_dichotom (patch, cursor, anew_patch, temp);
	}
	else if (find_bit (patch, *cursor))
	{
		(*cursor)++;
		set1_bit ((*anew_patch), bound[0]);
	}
	else
		(*cursor)++;
}

void		decompress_dichotom_1 (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size)
{
	int	cursor;
	int	bound[2] = {0};
	
	bound[1] = 8 * BUFFER_SIZE;
	cursor = 3;
	file_part_of_newpatch_dichotom (patch, &cursor, anew_patch, bound);
}

static void	file_part_of_newpatch_dichotom2 (char *patch, int *cursor, char (*anew_patch)[BUFFER_SIZE], int bound[2])
{
	int	temp[2];
	
	if (find_bit (patch, (*cursor)++))
	{
		while (bound[1] > bound[0])
			set_bit (*anew_patch, bound[0]++, find_bit(patch, (*cursor)++));
	}
	else if (find_bit (patch, (*cursor)++))
	{
		temp[0] = bound[0];
		temp[1] = (bound[1] + bound[0]) / 2;
		file_part_of_newpatch_dichotom2 (patch, cursor, anew_patch, temp);
		temp[0] = temp[1];
		temp[1] = bound[1];
		file_part_of_newpatch_dichotom2 (patch, cursor, anew_patch, temp);
	}
	else
	{
		while (bound[1] > bound[0])
			set0_bit (*anew_patch, bound[0]++);
	}
}

void		decompress_dichotom_2 (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size)
{
	int	cursor;
	int	bound[2] = {0};
	
	bound[1] = 8 * BUFFER_SIZE;
	cursor = 3;
	file_part_of_newpatch_dichotom2 (patch, &cursor, anew_patch, bound);
}
