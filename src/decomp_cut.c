#include "../includes/bit.h"
#include "../includes/server.h"
#include "../includes/decompress.h"
#include "../includes/point_changes.h"
#include <stdlib.h>

void	decompress_cut_end (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size)
{
	int	i;
	
	i = 3;
	while (i < 8 * patch_size - 1)
	{
		set_bit (*anew_patch, i - 3, (int)find_bit (patch, i));
		i++;
	}
}

void	decompress_cut_beginning (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size)
{
	int	i;
	
	i = 8 * patch_size - 2;
	while (i > 2)
	{
		set_bit (*anew_patch, 8 * BUFFER_SIZE - 8 * patch_size + 1 + i, (int)find_bit (patch, i));
		i--;
	}
}
