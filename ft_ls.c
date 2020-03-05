#include "ft_ls.h"

int main(int ac, char **av)
{
	t_infos *infos;

	infos = NULL;
	if(ac < 1 || av == NULL || av[1] == NULL || (!(infos_init(&infos))))
		return(-1);
	if(parser(av, infos) == -1)
		return(-1);
	return(0);
}
