#include "ft_ls.h"

int ft_strchr(char c, char *str)
{
	int x;
	x = -1;

	while(str[++x])
		if(str[x] == c)
			return(1);
	return(0);
}
int parser(char *str, char *flag)
{
	char *tmp;
	int len;
	flag = NULL;
	tmp = NULL;
	len = 0;
	if(ft_strchr('-', str) == 0)
		return(0);
	while(*str && *str != '-')
		++str;
	tmp = str;
	while(*(++tmp))
		len++;
	if(!(flag = (char *)malloc(sizeof(char) * len + 1)))
		return (-1);
	while(*(++str) && len > 0)
	{
		*flag = *(str);
		flag++;
	}
	*flag = '\0';
	flag -= sizeof(char) * len;
	while(*flag)
	{
		if(ft_strchr(*flag, FLAGS) == 0)
		{
			printf("ls: illegal option -- %c\nusage: ls [-ABCFGHLOPRSTUWabcdefghiklmnopqrstuwx1] [file ...]\n", *flag);
			return(-1);
		}
		flag++;
	}
	flag -= sizeof(char) * len;
	return(0);
}

int main(int ac, char **av)
{
	char *flag;
	flag = NULL;
	struct termios *termios_p = NULL;

	termios_p = (struct termios *)malloc(sizeof(*termios_p));
	tcgetattr(0, termios_p);

	if(ac < 1 || av == NULL || av[1] == NULL)
	{
		printf("ls [-lRartufgd] [file ...]\n");
		free(flag);
		return(-1);
	}
	printf("lebleulepkjrocrvcev\nijdvbu\nwichwcnc\n");
	if(parser(av[1], flag) == -1)
		return(-1);
	return(0);

}
