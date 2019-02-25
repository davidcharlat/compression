#include <string.h>
#include <stdlib.h>
#include "../includes/server.h"
#include "../includes/client.h"
#include "../includes/decompress.h"
#include "../includes/bit.h"
	#include <stdio.h>
/*
best compressions:

various size: 
char tab1[] = "azertyuiop123456aaaaaaaaaaaaaaaaaaaaaaaaa123456azertyuiop12345";
char tab2[] = "éertyuiop123456bbaaaaaabaaaaaaab        123456azertyuiop12346";

pt change bit size
char tab1[] = "azertyuiop123456aaaaaaaaaaaaaaaaaaaaaaaaa123456azertyuiop12345";
char tab2[] = "azdéyuiop123456aaaaaaaéaaaaaaaaaaaaaaaa123456azertyuiop123é";

cut begining
char tab1[] = "azertyuiop123456aaaaaaaaaaaaaaaaaaaaaaaaa123456azertyuiop12345";
char tab2[] = "azertyuiop123456aaaaaaaaaaaaaaaaaaaaaaaaa123456azertyuiop1234*";

cut end
char tab1[] = "azertyuiop123456aaaaaaaaaaaaaaaaaaaaaaaaa123456azertyuiop12345";
char tab2[] = "!zertyuiop123456aaaaaaaaaaaaaaaaaaaaaaaaa123456azertyuiop12345";

dichotom 2
char tab1[] = "azertyuiop123456bbbbaaaaaaaaaaaaaaaaabbbb123456azertyuiop12345";
char tab2[] = " z  tyuiop123456bbbbaaaaaaaaaaa    aabbbb123457965gy452jiuhrGT";

point changes
char tab1[] = "azertyuiop123456bbbbaaaaaaaaaaaaaaaaabbbb123456azertyuiop12345";
char tab2[] = "azertyuiop123456bbbbaaaaaaaaaaa aaaaabbbb123456 zertyuiop1    ";

dichotom1
char tab1[] = "azertyuiop123456bbbbaaaaaaaaaaaaaaaaabbbb123456azertyuiop12345";
char tab2[] = "azertyuiop123456bbbbaaaaaaaaaaaaaaaaabbbb123456czertzu*   /p923ty"; (without spaces)'

point changes size
char tab1[] = "azertyuiop123456bbbbaaaaaaaaaaaaaaaaabbbb123456azertyuiop12345";
char tab2[] = "az*   uiop12345*99 baaaaaaaaaaaaaaaaabbbb123456az*///uiop12345";

static int	verify (char* tab1, char* tab2, char* new_tab, int patch_size, char *patch)
{
	int i = 0;
	
	printf ("\nold str:    %s\nnew str:    %s\ndecomp str: %s\nsize: %d with compression: %d\n",
		tab1, tab2, new_tab, patch_size, 1 + bits_to_int(patch, &i, 3));
	free (patch);
	return (strncmp (tab2, new_tab, BUFFER_SIZE));
}

int main ()
{
	char tab0[BUFFER_SIZE] = {0};
	char tab1[] = "azertyuiop123456bbbbaaaaaaaaaaaaaaaaabbbb123456azertyuiop12345";
	char tab2[] = "az*   uiop12345*99 baaaaaaaaaaaaaaaaabbbb123456az*///uiop12345";
	char tab3[] = "azertyuiop123456bbbbaaaaaaaaaaaaaaaaabbbb123456czertzu*/p923ty";
	char tab4[] = "azertyuiop123456bbbbaaaaaaaaaaa aaaaabbbb123456 zertyuiop1    ";
	char tab5[] = "éertyuiop123456aabbaaaabaaaaaaab        123456azertyuiop12346";
	char tab6[] = "azdéyuiop123456bbbbaaaéaaaaaaaaaaaabbbb123456azertyuiop123é";
	char tab7[] = "azertyuiop123456bbbbaaaaaaaaaaaaaaaaabbbb123456azertyuiop1234*";
	char tab8[] = "!zertyuiop123456bbbbaaaaaaaaaaaaaaaaabbbb123456azertyuiop12345";
	char tab9[] = " z  tyuiop123456bbbbaaaaaaaaaaa    aabbbb123457965gy452jiuhrGT";
	char tabA[] = "azertyuiop123456bbbbaaaaaaaaaaa aaaaabbbb123456 zertyuiop1    ";
	char tabB[] = "azertyuiop123456bbbbaaaaaaaaaaa aaaaabbbblihlev545fvehoi/*+6em";
	char tabC[] = "ghgezj  hdjs skjdhk zioirr l aii ai  ei alihlev545fvehoi/*+6em";
	char	*patch;
	char	new_tab[BUFFER_SIZE + 1] = {0};
	int i = 0;
	int patch_size;
	
	printf ("test: starting with an empty buffer:");
	patch = buff_to_patch ((char*)tab0, tab1, &patch_size);
	patch_to_buff ((char*)tab0, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab0, (char*)tab1, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	printf ("OK\n\n\ntesting different compressions:");
	patch = buff_to_patch (tab1, tab7, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tab7, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
 	patch = buff_to_patch (tab1, tab3, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tab3, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab1, tab4, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tab4, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab1, tab2, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tab2, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab1, tab8, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tab8, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab1, tab6, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tab6, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab1, tab9, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tab9, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab1, tab5, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tab5, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	printf ("OK\n\n\nfew tests:");
	patch = buff_to_patch (tab1, tabA, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tabA, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab1, tab1, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tab1, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab0, tab0, &patch_size);
	patch_to_buff ((char*)tab0, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab0, (char*)tab0, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab1, tabB, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tabB, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab1, tabC, &patch_size);
	patch_to_buff ((char*)tab1, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab1, (char*)tabC, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tabA, tab7, &patch_size);
	patch_to_buff ((char*)tabA, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tabA, (char*)tab7, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tabB, tabC, &patch_size);
	patch_to_buff ((char*)tabB, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tabB, (char*)tabC, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tabC, tab9, &patch_size);
	patch_to_buff ((char*)tabC, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tabC, (char*)tab9, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	patch = buff_to_patch (tab3, tabA, &patch_size);
	patch_to_buff ((char*)tab3, patch, patch_size, (char*)new_tab);
	if (verify ((char*)tab3, (char*)tabA, (char*)new_tab, patch_size, patch))
		return (printf("error\n"));
	printf ("OK\n");
	return (0);
}
