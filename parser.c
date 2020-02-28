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

int flags_infos(char *str, int ret, t_infos *infos)
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
int ft_memalloc(t_infos *infos, int len)
{
	char *tmp;
	char *tmp_join;
	int ret;
	ret = 0;
	tmp = NULL;
	tmp_join = NULL;
	if(infos->name == NULL)
	{
		if(!(infos->name = ft_strnew(len + 1)))
			return(-1);
	}
	else
	{
		if(!(tmp_join = ft_strjoin(infos->name, tmp = ft_strnew(len + 1))))
			return(-1);
		ft_strdel(infos->name);
		infos->name = tmp_join;
		ret = len;
	}
	return(ret);
}
int file_infos(char *str, t_infos *infos)
{
	int len;
	char *tmp;
	int len_malloc;
	tmp = NULL;
	len_malloc = 0;
	len = 0;

	tmp = str;
	while(*tmp != ' ' && *tmp)
	{
		tmp++;
		len++;
	}
	if((len_malloc = ft_memalloc(infos, len)) == -1)
		return(-1);
	infos->name += len_malloc;
	while(str != tmp)
	{
		*infos->name = *str;
		infos->name++;
		str++;
	}
	return(len);
}

int parser(char *str, t_infos *infos)
{
	int ret;
	int ret_total;
	ret_total = 0;
	ret = 0;

	if((ret = ft_strchr('-', str)) != -1)
		if((ret = flags_infos(str, ret + 1, infos)) == -1)
			return (-1);
	if(ret > -1)
		str += ret;
	while(*str)
	{
		if(*str != ' ' && *str)
		{
			if((ret = file_infos(str, infos)) == -1)
				return(-1);
			str += ret;
			infos->nb_files++;
			ret_total += ret;
		}
		str++;
		ret = 0;
		infos->name -= ret_total;
	}
	return(0);
}
int infos_init(t_infos **infos)
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
	if(parser(av[1], infos) == -1)
		return(-1);
	printf("%s\n", infos->name);
	return(0);

}
