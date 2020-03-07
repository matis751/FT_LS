#include "ft_ls.h"

int get_row_col(struct dirent *dp, int *row, int *ret_col, int size, int max_len)
{
	struct winsize ws;
	int col = 0;
	int x = 0;
	int col_max = 0;
	ioctl(STDIN_FILENO, TIOCGWINSZ, &ws);
	col = ws.ws_col;
	printf("%d col \n name_len ==========> %d\n",col, dp->d_namlen);
	while(size--)
	{
		if(dp == NULL)
			break;
		printf("col_term %d \n name_len ==========> %d\n",col, dp->d_namlen);
		if(dp->d_namlen < col)
		{
			col -= dp->d_namlen + max_len - dp->d_namlen + 1;
			dp++;
			if(x++ > *ret_col)
				(*ret_col = x);
		}
		else
		{
			col = ws.ws_col;
			x = 0;
			(*row)++;
		}
	}
	return(max_len);
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
	printf("ICI line %d col %d\n",r,c);
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
