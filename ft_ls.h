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
