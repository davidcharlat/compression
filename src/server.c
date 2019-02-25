#include <stdlib.h>
#include "../includes/server.h"
#include "../includes/bit.h"

char	*buff_to_patch (char *buff_n, char *buff_n_1, int *patch_size)
{
	int		size;
	int 	protocole;
	char	*patch;
	
	size = BUFFER_SIZE * 3 + 4;
	protocole = 0;
	if (!(patch = (char*)malloc(size)))
		return (patch);
	if (size > cut_beginning (buff_n, buff_n_1, patch))
		size = cut_beginning (buff_n, buff_n_1, patch);
	if (size > dichotom_1 (buff_n, buff_n_1, patch) && (protocole = 1))
		size = dichotom_1 (buff_n, buff_n_1, patch);
	if (size >  pointchanges_size (buff_n, buff_n_1, patch) && (protocole = 3))
		size = pointchanges_size (buff_n, buff_n_1, patch);
	if (size >  point_changes (buff_n, buff_n_1, patch) && (protocole = 2))
		size = point_changes (buff_n, buff_n_1, patch);
	if (size >  cut_end (buff_n, buff_n_1, patch) && (protocole = 4))
		size = cut_end (buff_n, buff_n_1, patch);
	if (size >  pointchanges_bit_size (buff_n, buff_n_1, patch) && (protocole = 5))
		size = pointchanges_bit_size (buff_n, buff_n_1, patch);
	if (size >  dichotom_2 (buff_n, buff_n_1, patch) && (protocole = 6))
		size = dichotom_2 (buff_n, buff_n_1, patch);
	if (size >  pts_bit_various_size (buff_n, buff_n_1, patch) && (protocole = 7))
		size = pts_bit_various_size (buff_n, buff_n_1, patch);
	if (protocole == 0)
		*patch_size = cut_beginning (buff_n, buff_n_1, patch);
	if (protocole == 1)
		*patch_size = dichotom_1 (buff_n, buff_n_1, patch);
	if (protocole == 2)
		*patch_size = point_changes (buff_n, buff_n_1, patch);
	if (protocole == 3)
		*patch_size = pointchanges_size (buff_n, buff_n_1, patch);
	if (protocole == 4)
		*patch_size = cut_end (buff_n, buff_n_1, patch);
	if (protocole == 5)
		*patch_size = pointchanges_bit_size (buff_n, buff_n_1, patch);
	if (protocole == 6)
		*patch_size = dichotom_2 (buff_n, buff_n_1, patch);
	if (protocole == 7)
		*patch_size = pts_bit_various_size (buff_n, buff_n_1, patch);
	return (patch);
}
