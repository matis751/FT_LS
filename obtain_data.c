#include "ft_ls.h"
void print_mode(struct stat *buf)
{
	printf( (S_ISDIR(buf->st_mode)) ? "d" : "-");
	printf( (buf->st_mode & S_IRUSR) ? "r" : "-");
	printf( (buf->st_mode & S_IWUSR) ? "w" : "-");
	printf( (buf->st_mode & S_IXUSR) ? "x" : "-");
	printf( (buf->st_mode & S_IRGRP) ? "r" : "-");
	printf( (buf->st_mode & S_IWGRP) ? "w" : "-");
	printf( (buf->st_mode & S_IXGRP) ? "x" : "-");
	printf( (buf->st_mode & S_IROTH) ? "r" : "-");
	printf( (buf->st_mode & S_IWOTH) ? "w" : "-");
	printf( (buf->st_mode & S_IXOTH) ? "x" : "-");
}

void free_f(struct stat *buf, struct passwd *uid, struct group *grp, struct dirent *dir)
{
	free(buf);
	buf = NULL;
	uid = NULL;
	grp = NULL;
	dir = NULL;
}
int main(int ac, char **av)
{
	struct stat *buf = NULL;
	struct passwd *uid = NULL;
	struct group *grp = NULL;
	struct dirent *dir = NULL;
	DIR *dp = NULL;
	char *time_str;
	if(ac <= 1)
	{
		perror("errno");
		return(-1);
	}
	buf = (struct stat *)malloc(sizeof(*buf));
	if(stat(av[1], buf) == -1)
	{
		printf("1\n");
		perror("errno");
		return(-1);
	}
	if(!(dp = (opendir("."))))
	{
		perror("errno");
		return(-1);
	}
	while((dir = readdir(dp)) != NULL)
	{
		if(strcmp(av[1], dir->d_name) == 0)
			break;
	}
	printf("%s\n%hhu\n", dir->d_name, dir->d_type);
	if(!(time_str = ctime(&buf->st_mtimespec.tv_sec)) || !(uid = getpwuid(buf->st_uid)) || !(grp = getgrgid(buf->st_gid)))
	{
		perror("errno");
		return(-1);
	}
	printf("%s\n%s\n", grp->gr_name, *grp->gr_mem);
	printf("%s\n%hu\n%lld\n%hu\n%s\n", uid->pw_name, buf->st_nlink, buf->st_size, buf->st_mode, time_str);
	print_mode(buf);
	/*printf("name : %s\ntype : %s\nModes : %s\nNombres de liens : %d\n", *av, buf);
*/	free_f(buf, uid, grp, dir);
	closedir(dp);
	return(0);
}
