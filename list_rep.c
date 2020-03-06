#include "ft_ls.h"

int get_row_col(struct dirent *dp, int *row, int *ret_col, int size, int max_len)
{
	struct winsize ws;
	int len = size;
	int col = 0;
	int col_max = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	col = ws.ws_col;
	while(len--)
	{
		printf("OUI\n\n");
		if(dp == NULL)
			break;
		if(dp->d_namlen < col)
		{
			col -= dp->d_namlen + max_len - dp->d_namlen + 1;
			dp++;
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
	return(max_len);
}

void alpha_sort_list(t_dir **tmp_dir, int size, int *max_len)
{
	int x;
	int col = 0;
	int row = 1;
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
/*	*max_len = get_row_col(ret, &row, &col, size);*/
	column_sort(&ret, row, col, row > col ? row : col, *max_len);
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
int select_print(t_dir **tmp, char *options)
{
	t_dir *ret = NULL;
	t_dir *dir = NULL;
	t_dir *ret_ = NULL;
	int len = 0;
	dir = *tmp;
	if(!(init_dir(&ret)))
		return(-1);
	ret_ = ret;
	while(dir != NULL)
	{
		if(dir->dp == NULL)
			break;
		if(dir->dp->d_name[0] != '.')
		{
			ret->dp = dir->dp;
			if(dir->next != NULL)
			{
				if(!(init_dir(&ret->next)))
					return(-1);
				ret = link_dir(ret, ret->next);
				len++;
			}
		}
		dir = dir->next;
	}
	*tmp = ret_;
	return(len);
}
void options(t_dir **dir, int *max_len)
{
	int size = 0;
	t_dir *str_dir = NULL;
	str_dir = *dir;
	size = select_print(&str_dir, "a");
	alpha_sort_list(&str_dir,size, max_len);
	*dir = str_dir;
}
void column_sort(t_dir **dir, int row, int col, int tab, int max_len)
{
	t_dir ret[tab][tab];
	t_dir mod[tab][tab];
	t_dir *sort = NULL;
	sort = *dir;
	int c = 0;
	int x = 0;
	int y = 0;
	int r = 0;
	int len = 0;
	int ter_col = 0;
	int len_2 = 0;
	struct winsize ws;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	ter_col = ws.ws_col;
	ft_memset(ret, 0, row*col*sizeof(**ret));
	ft_memset(mod, 0, row*col*sizeof(**ret));
	while(c < col)
	{
		while(r < row)
		{
			if(sort->dp == NULL)
				break;
			ret[r][c].dp = sort->dp;
			mod[x][y].dp = ret[r][c].dp; 
			printf("r %d c %d ==============>> %s ===========>len %d\n", r , c , ret[r][c].dp->d_name, len++);
			printf("y %d x %d ==============>> %s ===========>len %d\n", r , c , mod[y][x].dp->d_name, len_2++);
			sort = sort->next;
			y++;
			if(y > col)
				y = 0;
			r++;
		}
		printf("\n");
		c++;
		x++;
		if(x > row)
			x = 0;
		r = 0;
	}
	c = 0;
	x = 0;
	y = 0;
	r = 0;
	printf("r %d c %d\n\n", row,col);
	len = 0;
	while(y <= row)
	{
		while(x <= col)
		{
			if(mod[x][y].dp == NULL)
				break;
			if(mod[x][y].dp->d_namlen < ter_col)
			{
				print_name_dir(mod[x][y].dp, max_len - mod[x][y].dp->d_namlen + 1);
				ter_col -= mod[x][y].dp->d_namlen + max_len - mod[x][y].dp->d_namlen + 1;
				x++;
			}
			else
			{
				printf("\n");
				ter_col = ws.ws_col;
			}
		}
		x = 0;
		y++;
	}
}
void display_options(t_dir *str_dir)
{
	struct winsize ws;
	int col = 0;
	int max_len = 0;
	int x;
	x = 0;
	t_dir ** displ = NULL;
	t_dir *ret = NULL;
	t_dir *print = NULL;
	ret = str_dir;
	options(&str_dir, &max_len);
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
int get_max_len(t_dir *dir, int size)
{
	int len;
	len = 0;

	while(size-- > 0)
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
	int r = 0;
	int c = 0;
	int x = 0;
	int y = 0;
	struct dirent *dp = NULL;
	struct dirent **point = NULL;

	dp = *list;
	max_len = get_max_len_dir(list, size);
	get_row_col(dp, &r, &c, size,max_len);
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	col = ws.ws_col;
	printf("line %d col %d\n",r,c);
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
	/*if(dir_list(dp, dirp, &str_dir) == -1)
		return(-1);
	display_options(str_dir);
	*/
	dp = readdir(dirp);
	if((size = scandir(dp->d_name, &list, NULL, alphasort)) == -1)
		return(-1);
	display_op(list, size);
	if(closedir(dirp) == -1)
	{
		printf("ERROR\n");
		return(-1);
	}
	return(0);
}
