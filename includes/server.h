#ifndef SERVER_H
# define SERVER_H 

# define BUFFER_SIZE 62

int		cut_end (char *buff_n, char *buff_n_1, char *patch);
int		cut_beginning (char *buff_n, char *buff_n_1, char *patch);
int		dichotom_1 (char *buff_n, char *buff_n_1, char *patch);
int		point_changes (char *buff_n, char *buff_n_1, char *patch);
int		pointchanges_size (char *buff_n, char *buff_n_1, char *patch);
int		pointchanges_bit_size (char *buff_n, char *buff_n_1, char *patch);
int		dichotom_2 (char *buff_n, char *buff_n_1, char *patch);
int		pts_bit_various_size (char *buff_n, char *buff_n_1, char *patch);
char	*buff_to_patch (char *buff_n, char *buff_n_1, int *patch_size);

#endif
