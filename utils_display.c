#include "ft_ls.h"

t_dir *link_dir(t_dir *dir_1, t_dir *dir_2)
{
	t_dir *tmp = NULL;
	if(dir_1 == NULL || dir_2 == NULL)
		return(NULL);
	tmp = dir_1;
	dir_1->next = dir_2;
	dir_2->prec = tmp;
	return (dir_2);
}

void *init_dir(t_dir **dir)
{
	t_dir *tmp = NULL;
	if(!(tmp = (t_dir *)malloc(sizeof(t_dir))))
		return(NULL);
	tmp->prec = NULL;
	tmp->dp = NULL;
	tmp->next = NULL;
	tmp->sw = 0;
	*dir = tmp;
	return((void *)dir);
}
int dir_list(struct dirent *dp, DIR *dirp, t_dir **str)
{
	t_dir *str_dir = NULL;
	t_dir *tmp = NULL;
	str_dir = NULL;
	str_dir = *str;

	while((dp = readdir(dirp)) != NULL)
	{
		if(tmp == NULL)
			tmp = str_dir;
		if(str_dir == NULL)
			if(!(init_dir(&str_dir)))
				return(-1);
		str_dir->dp = dp;
		if(!(init_dir(&str_dir->next)))
			return(-1);
		if(!(str_dir = link_dir(str_dir, str_dir->next)))
			return(-1);
	}
	*str = tmp->prec;
	return(1);
}

void switch_dir(t_dir *dir_1, t_dir *dir_2)
{
	t_dir *tmp = NULL;
	tmp = dir_1;
	dir_1 = dir_2;
	dir_2 = tmp;
}

int switch_d_dir(t_dir **tdir_1, t_dir **tdir_2)
{
	struct dirent *tmp = NULL;
	t_dir *dir_1 = NULL;
	t_dir *dir_2 = NULL;
	dir_1 = *tdir_1;
	dir_2 = *tdir_2;
	dir_1->sw = 1;
	dir_2->sw = 1;
	if(dir_1 == NULL || dir_1->dp == NULL || dir_2 == NULL || dir_2->dp == NULL)
		return(-1);
	tmp = dir_1->dp;
	dir_1->dp = dir_2->dp;
	dir_2->dp = tmp;

	*tdir_1 = dir_1;
	*tdir_2 = dir_2;
	return(1);

}

void top_list_sw(t_dir *dir_1, t_dir *dir_2)
{
	t_dir *tmp;
	tmp = NULL;

	while(dir_1->prec != NULL)
	{
		tmp = dir_1;
		dir_1 = dir_1->prec;
		dir_1->next = tmp;
	}
	switch_dir(dir_1, dir_2);
}
t_dir *mov_dir(t_dir *dir, int nb)
{
	t_dir *tmp = NULL;
	if(dir == NULL)
		return(NULL);
	if(nb == 0)
		return(dir);
	tmp = dir;
	while(nb--)
	{
		if(tmp->next == NULL)
			return(NULL);
		tmp = tmp->next;
	}
	return(tmp);
}
