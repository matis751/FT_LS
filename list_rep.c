#include "ft_ls.h"

t_dir *link_dir(t_dir *dir_1, t_dir *dir_2)
{
	if(dir_1 == NULL || dir_2 == NULL)
		return(NULL);
	dir_1->next = dir_2;
	dir_2->prec = dir_1;
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
	t_dir *str_dir;
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
		str_dir = link_dir(str_dir, str_dir->next);
	}
	*str = tmp;
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

void get_row_col(t_dir *dir, int *row, int *ret_col)
{
	struct winsize ws;
	int col = 0;
	int max_len = 0;
	int col_max = 0;
	max_len = get_max_len(dir);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	col = ws.ws_col;
	while(dir != NULL)
	{
		if(dir->dp == NULL)
			break;
		if(dir->dp->d_namlen < col)
		{
			col -= dir->dp->d_namlen + max_len - dir->dp->d_namlen + 1;
			dir = dir->next;
			if(col_max == 0)
				(*ret_col)++;
		}
		else
		{
			col = ws.ws_col;
			col_max = 1;
			(*row)++;
		}
	}
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
void column_sort(t_dir **dir, int row, int col)
{
	t_dir ret[row + 1][col + 1];
	t_dir *sort = NULL;
	sort = *dir;
	int r = 0;
	int c = 0;
	int x = 0;
	int y = 0;

	r = row;
	c = col;
	while(c > 0)
	{
		while(r >= 0)
		{
			ret[x][y] = *sort;
			y++;
			r--;
			sort = sort->next;
		}
		r = row;
		c--;
		x++;
		y = 0;
	}
	x = 0;
	y = 0;
	sort = *dir;
	while (x < col)
	{
		while (y <= row)
		{
			sort->dp = ret[y][x].dp;
			printf("%s\n",sort->dp->d_name);
			y++;
			if(sort->next == NULL)
				break;
			sort = sort->next;
		}
		y = 0;
		x++;
		if(sort->next == NULL)
			break;
	}
}
void alpha_sort_list(t_dir **tmp_dir)
{
	int x;
	int col = 0;
	int row = 0;
	t_dir *dir = NULL;
	t_dir *tmp = NULL;
	t_dir *ret = NULL;
	dir = *tmp_dir;
	tmp = dir;
	ret = dir;
	x = 0;
	while(dir != NULL)
	{
		if(tmp->dp)
			if(dir->dp)
				if(tmp->dp->d_name[x])
					if(dir->dp->d_name[x])
						if(tmp->dp->d_name[x] <= dir->dp->d_name[x])
						{
							if(tmp->dp->d_name[x] == dir->dp->d_name[x])
							{
								while(tmp->dp->d_name[x] == dir->dp->d_name[x]
									&& tmp->dp->d_name[x] && dir->dp->d_name[x])
									x++;
							}
							if(tmp->dp->d_name[x] <= dir->dp->d_name[x])
								top_list_sw(tmp, dir);
							x = 0;
						}
				dir = link_dir(dir, dir->next);
			}
	*tmp_dir = ret;
	get_row_col(ret, &row, &col);
	column_sort(&ret, row, col);
}

void    print_name(t_dir *dir, int num_sp)
{
	if((access(dir->dp->d_name, X_OK) != -1) && (dir->dp->d_type == DT_REG))
		printf(RED "%s",dir->dp->d_name);
	if((access(dir->dp->d_name, X_OK) == -1) && (dir->dp->d_type == DT_REG))
		printf(WHT"%s",dir->dp->d_name);
	if(dir->dp->d_type == DT_DIR)
		printf(CYN"%s",dir->dp->d_name);
	while(num_sp--)
		printf(" ");
}
void    print_name_dir(struct dirent *dp, int num_sp)
{
	if((access(dp->d_name, X_OK) != -1) && (dp->d_type == DT_REG))
		printf(RED "%s",dp->d_name);
	if((access(dp->d_name, X_OK) == -1) && (dp->d_type == DT_REG))
		printf(WHT"%s",dp->d_name);
	if(dp->d_type == DT_DIR)
		printf(CYN"%s",dp->d_name);
	while(num_sp--)
		printf(" ");
}
void display_options(t_dir *str_dir)
{
	struct winsize ws;
	int col = 0;
	int max_len = 0;
	int x;
	x = 1;
	t_dir *ret = NULL;
	ret = str_dir;
	max_len = get_max_len(str_dir);

	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	col = ws.ws_col;
	while(str_dir != NULL)
	{
		if(str_dir->dp == NULL)
			break;
		if(str_dir->dp->d_name[0] != '.')
		{
			if(str_dir->dp->d_namlen < col)
			{
				print_name(str_dir, max_len - str_dir->dp->d_namlen + 1);
				col -= str_dir->dp->d_namlen + max_len - str_dir->dp->d_namlen + 1;
				str_dir = str_dir->next;
			}
			else
			{
				printf("\n");
				col = ws.ws_col;
			}
		}
		else
			str_dir = str_dir->next;
	}
	str_dir = ret;
}

int get_max_len_dir(struct dirent **list, int size)
{
	int len;
	struct dirent *dp = NULL;
	len = 0;

	while(size--)
	{
		dp = *list;
		if(dp->d_namlen > len)
			len = dp->d_namlen;
		*(list++);
	}
	return(len);
}
int get_max_len(t_dir *dir)
{
	int len;
	len = 0;

	while(dir->dp)
	{
		if(dir->dp->d_namlen > len)
			len = dir->dp->d_namlen;
		dir = dir->next;
	}
	return(len);
}
void display_op(struct dirent **list, int size)
{
	struct winsize ws;
	int col = 0;
	int max_len = 0;
	struct dirent *dp = NULL;
	max_len = get_max_len_dir(list, size);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	col = ws.ws_col;
	while(size--)
	{
		dp = *list;
		if(dp == NULL)
			break;
		if(dp->d_name[0] != '.')
		{
			if(dp->d_namlen < col)
			{
				print_name_dir(dp, max_len - dp->d_namlen + 1);
				col -= dp->d_namlen + max_len - dp->d_namlen + 1;
				*(list++);
			}
			else
			{
				printf("\n");
				col = ws.ws_col;
				size++;
			}
		}
		else
			*(list++);
	}
}
int main()
{
	struct dirent *dp = NULL;
	struct dirent **list = NULL;
	DIR *dirp = NULL;
	int size = 0;
	t_dir *str_dir = NULL;
	dirp = opendir(".");
	if (dirp == NULL)
		printf ("ERROR\n");
	if(dir_list(dp, dirp, &str_dir) == -1)
		return(-1);
	alpha_sort_list(&str_dir);
	display_options(str_dir);
/*
	dp = readdir(dirp);
	if((size = scandir(dp->d_name, &list, NULL, alphasort)) == -1)
		return(-1);
	display_op(list, size);
*/
	if(closedir(dirp) == -1)
	{
		printf("ERROR\n");
		return(-1);
	}
	return(0);
}
