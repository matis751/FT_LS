/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mel-oual <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 05:18:09 by mel-oual          #+#    #+#             */
/*   Updated: 2020/02/28 05:18:14 by mel-oual         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int ft_strchr(char c, char *str)
{
	int x;
	x = -1;

	while(str[++x])
		if(str[x] == c)
			return(x);
	return(-1);
}

int flags_infos(char *str, int ret, t_infos *infos)/*enregistres les flags et renvoies une erreur en cas d'options incorrectes'*/
{
	char *tmp;
	int len;
	char *flags;
	flags = NULL;
	tmp = NULL;
	len = 0;
	str += ret;
	tmp = str;

	while(*tmp && *tmp != ' ')
		tmp++;
	len = tmp - str;
	if(!(flags = (char *)malloc(sizeof(char) * len + 1)))
		return (-1);
	while(*str && *str != ' ')
	{
		*flags = *(str);
		flags++;
		str++;
	}
	*flags = '\0';
	flags -= sizeof(char) * len;
	while(*flags)
	{
		if(ft_strchr(*flags, FLAGS) == -1)
		{
			printf("ls: illegal option -- %c\nusage: ls [-lRartufgd] [file ...]\n", *flags);
			return(-1);
		}
		flags++;
	}
	flags -= sizeof(char) * len;
	infos->flags = flags;
	return(len + ret);
}
int nb_file(t_infos *infos, char **av, int *var) /*calcul le nb de files passes en parametres*/
{
	int x;
	x = 0;

	while(av[++x] != NULL)
		if(ft_strchr('-', av[x]) > -1)
		{
			if(av[x] != av[1])
				return(-1);
		}
	x--;
	if(ft_strchr('-', av[1]) > -1)
		*var += 1;
	infos->nb_files = x;
	return(x);
}

int parser(char **av, t_infos *infos) /*Ecrit le nom des fichier passer en parametres et les option dans une struct "infos"*/
{
	char *str;
	int ret;
	int len;
	int x;
	x = 0;
	len = 0;
	ret = 0;
	str = NULL;

	str = av[1];
	if((infos->nb_files = nb_file(infos, av, &x)) == -1)
		return(-1);
	infos->name = (char **)malloc(sizeof(char) * infos->nb_files);
	len = ft_strlen(str);
	if((ret = ft_strchr('-', str)) != -1)
		if((ret = flags_infos(str, ret + 1, infos)) == -1)
			return (-1);
	while(++x <= infos->nb_files)
		infos->name[x] = ft_strdup(av[x]);
	return(0);
}
int infos_init(t_infos **infos) /*iinitialise la structure infos*/
{
	t_infos *tmp;
	if(!(*infos = (t_infos *)malloc(sizeof(t_infos))))
		return(0);
	tmp = *infos;
	tmp->name = NULL;
	tmp->flags = NULL;
	tmp->nb_files = 0;
	return(1);

}

int main(int ac, char **av)
{
	t_infos *infos;

	infos = NULL;
	if(!(infos_init(&infos)))
		return(-1);
	if(ac < 1 || av == NULL || av[1] == NULL)
	{
		free(infos);
		return(-1);
	}
	if(parser(av, infos) == -1)
		return(-1);
	return(0);

}
