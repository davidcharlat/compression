#include "../includes/bit.h"
#include "../includes/server.h"
#include "../includes/decompress.h"
#include "../includes/point_changes.h"
#include <stdlib.h>

void	decompress_pointchanges_bit_size (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size)
{
	int patch_cursor;
	int	number_of_bit;
	int point;
	int	i;
	
	patch_cursor = 3;
	number_of_bit = bits_to_int (patch, &patch_cursor, 8) + 1;
	while ((patch_cursor + 1 + BUFFSIZE_BIT + 2) / 8 < patch_size)
	{
		point = bits_to_int (patch, &patch_cursor, BUFFSIZE_BIT + 3);
		set_bit (*anew_patch, point, 1);
		i = 1;
		while (i < number_of_bit && (patch_cursor) / 8 < patch_size && point + i < 8 * BUFFER_SIZE)
		{
			set_bit (*anew_patch, point + i, find_bit (patch, patch_cursor));
			patch_cursor++;
			i++;
		}
	}
}

void	decompress_pointchanges_size (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size)
{
	int patch_cursor;
	int	number_of_char;
	int point;
	int	i;
	
	patch_cursor = 3;
	number_of_char = bits_to_int (patch, &patch_cursor, 4) + 1;
	while ((patch_cursor + 8 + BUFFSIZE_BIT - 1) / 8 < patch_size)
	{
		point = bits_to_int (patch, &patch_cursor, BUFFSIZE_BIT);
		i = 0;
		while (i < number_of_char && (patch_cursor + 7) / 8 < patch_size)
		{
			(*anew_patch)[point + i] = bits_to_int (patch, &patch_cursor, 8);
			i++;
		}
	}
}

void	decompress_point_changes (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size)
{
	int patch_cursor;
	int	point;
	int	i;
	
	patch_cursor = 3;
	while ((patch_cursor + 7 + BUFFSIZE_BIT) / 8 < patch_size)
	{
		point = bits_to_int (patch, &patch_cursor, BUFFSIZE_BIT);
		(*anew_patch)[point] = bits_to_int (patch, &patch_cursor, 8);
	}
}

void	decompress_various_size (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size)
{
	int patch_cursor;
	int	number_of_bit;
	int point;
	int	i;
	
	patch_cursor = 4;
	while ((patch_cursor + 2 * BUFFSIZE_BIT + 6) < patch_size * 8)
	{
		number_of_bit = bits_to_int (patch, &patch_cursor, BUFFSIZE_BIT + 3);
		point = bits_to_int (patch, &patch_cursor, BUFFSIZE_BIT + 3);
		i = 1;
		set_bit (*anew_patch, point, 1);
		while (i < number_of_bit - 1 && (patch_cursor) / 8 < patch_size && point + i + 1 < 8 * BUFFER_SIZE)
		{
			set_bit (*anew_patch, point + i, find_bit (patch, patch_cursor));
			patch_cursor++;
			i++;
		}
		if (number_of_bit > 1)
			set_bit (*anew_patch, point + i, 1);
	}
}

