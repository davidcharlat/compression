#ifndef BIT_H
# define BIT_H 

_Bool	find_bit (char *tab, int n);
void	inv_bit (char *tab, int n);
void	set0_bit (char *tab, int n);
void	set1_bit (char *tab, int n);
void	set_bit (char *tab, int n, int val);
int		bits_to_int (char *patch, int *apatch_cursor, int nb_of_bit);

#endif
