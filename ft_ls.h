#include <fcntl.h>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <uuid/uuid.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FLAGS "lRartufgd"

typedef struct s_infos
{
	int nb_files;
	char *flags;
	char *name;
}t_infos;

void ft_strdel(char *str);
char *ft_strjoin(char *s1, char *s2);
char *ft_strnew(int len);
int ft_strlen(const char *str);
