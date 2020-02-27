#include <sys/types.h>
#include <sys/dir.h>
#include <stdio.h>


int main()
{
	struct dirent *dp = NULL;
	DIR *dirp = NULL;
	dirp = opendir(".");
	 if (dirp == NULL)
		printf ("ERROR\n");
	while((dp = readdir(dirp)) != NULL)
		printf("%s\n", dp->d_name);
	if(closedir(dirp) == -1)
	{
		printf("ERROR\n");
		return(-1);
	}
	return(0);
}
