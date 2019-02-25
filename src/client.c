#include "../includes/bit.h"
#include "../includes/server.h"
#include "../includes/decompress.h"
#include "../includes/point_changes.h"
#include <stdlib.h>

char		*patch_to_buff (char* buff_n_1, char* patch, int patch_size, char *new_buff)
{
	char	new_patch[BUFFER_SIZE] = {0};
	int		i;
	
	i = 0;
	if (!find_bit (patch, 0) && !find_bit (patch, 1) && find_bit (patch, 2))
		decompress_dichotom_1 (patch, &new_patch, patch_size);
	if (!find_bit (patch, 0) && find_bit (patch, 1) && !find_bit (patch, 2))
		decompress_point_changes (patch, &new_patch, patch_size);
	if (!find_bit (patch, 0) && find_bit (patch, 1) && find_bit (patch, 2))
		decompress_pointchanges_size (patch, &new_patch, patch_size);
	if (!find_bit (patch, 0) && !find_bit (patch, 1) && !find_bit (patch, 2))
		decompress_cut_beginning (patch, &new_patch, patch_size);
	if (find_bit (patch, 0) && !find_bit (patch, 1) && !find_bit (patch, 2))
		decompress_cut_end (patch, &new_patch, patch_size);
	if (find_bit (patch, 0) && !find_bit (patch, 1) && find_bit (patch, 2))
		decompress_pointchanges_bit_size (patch, &new_patch, patch_size);
	if (find_bit (patch, 0) && find_bit (patch, 1) && !find_bit (patch, 2))
		decompress_dichotom_2 (patch, &new_patch, patch_size);
	if (find_bit (patch, 0) && find_bit (patch, 1) && find_bit (patch, 2) && !find_bit (patch, 3))
		decompress_various_size (patch, &new_patch, patch_size);
	while (i < 8 * BUFFER_SIZE)
	{
		set_bit (new_buff, i, find_bit(buff_n_1, i) ^ find_bit(new_patch, i));
		i++;
	}
	return (new_buff);
}
