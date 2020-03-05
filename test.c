#include "ft_ls.h"

int main(void)
{
	int size;
	int len = 0;
	struct dirent **list = NULL;
	struct dirent *dp = NULL;
	struct stat     info;
	DIR *dirp = NULL;
	size = 0;
	dirp = opendir(".");
	if (dirp == NULL)
		printf ("ERROR\n");
	dp = readdir(dirp);
	size = scandir(dp->d_name, &list, NULL, alphasort);
	while(size--)
	{
		dp = *list;
		printf("%s\n",dp->d_name);
		*(list++);
	}
	(void)closedir(dirp);
	return (-1);
}
