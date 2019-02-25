#ifndef DECOMPRESS_H
# define DECOMPRESS_H

#include "../includes/server.h"

void	decompress_dichotom_1 (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size);
void	decompress_point_changes (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size);
void	decompress_pointchanges_size (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size);
void	decompress_cut_end (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size);
void	decompress_cut_beginning (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size);
void	decompress_pointchanges_bit_size (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size);
void	decompress_dichotom_2 (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size);
void	decompress_various_size (char *patch, char (*anew_patch)[BUFFER_SIZE], int patch_size);

#endif
