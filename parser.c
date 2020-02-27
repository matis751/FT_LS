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
/*int file_infos(char *str, t_infos *infos)
{


}
*/
int parser(char *str, t_infos *infos)
{
	int ret;
	ret = 0;

	if((ret = ft_strchr('-', str)) != -1)
		if((ret = flags_infos(str, ret + 1, infos)) == -1)
			return (-1);
	str += ret;
	while(*(str++))
		if(*str != ' ' && *str)
		{
			if((ret = file_infos(str, infos)) == -1);
				return(-1);
			str += ret;
		}
	printf("%c\n", *str);
	return(0);
}

int main(int ac, char **av)
{
	t_infos *infos;

	infos = NULL;
	if(!(infos = (t_infos *)malloc(sizeof(t_infos))))
		return(-1);
	if(ac < 1 || av == NULL || av[1] == NULL)
	{
		free(infos);
		return(-1);
	}
	if(parser(av[1], infos) == -1)
		return(-1);
	return(0);

}
