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



/**** COLOR ****/

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"



/**** TYPEDEF ****/

typedef struct s_infos
{
	int nb_files;
	char *flags;
	char **name;
}t_infos;

typedef struct s_dir
{

	struct s_dir *prec;
	struct dirent *dp;
	int sw;
	struct s_dir *next;

}t_dir;


typedef struct s_disp
{
	char **name;

}t_disp;



/**** FUNCTION ****/

/**** UTILS_LIBFT.C ****/
void ft_strdel(char *str);
void *ft_memset(void *b, int c, size_t len);
char *ft_strjoin(char *s1, char *s2);
char *ft_strdup(char *str);
char *ft_strndup(char *str, int i);
char *ft_strnew(int len);
int ft_strchr(char c, char *str);
int ft_strlen(const char *str);
int infos_init(t_infos **infos);
int parser(char **av, t_infos *infos);
int nb_file(t_infos *infos, char **av, int *var);
int flags_infos(char *str, int ret, t_infos *infos);

/**** LIST_REP.C ****/

void display_op(struct dirent **list, int size);
int get_max_len(t_dir *dir, int size);
int get_max_len_dir(struct dirent **dp, int size);
void display_options(t_dir *str_dir);
void    print_name_dir(struct dirent *dp, int num_sp);
void    print_name(t_dir *dir, int num_sp);
void alpha_sort_list(t_dir **tmp_dir,int size, int *max_len);
void top_list_sw(t_dir *dir_1, t_dir *dir_2);
void switch_dir(t_dir *dir_1, t_dir *dir_2);
int dir_list(struct dirent *dp, DIR *dirp, t_dir **str);
void *init_dir(t_dir **dir);
t_dir *link_dir(t_dir *dir_1, t_dir *dir_2);
void column_sort(t_dir **dir, int row, int col, int tab, int max_len);


/**** UTILS_DISPLAY.C ****/
t_dir *link_dir(t_dir *dir_1, t_dir *dir_2);
void *init_dir(t_dir **dir);
int dir_list(struct dirent *dp, DIR *dirp, t_dir **str);
void switch_dir(t_dir *dir_1, t_dir *dir_2);
int switch_d_dir(t_dir **tdir_1, t_dir **tdir_2);
t_dir *mov_dir(t_dir *dir, int nb);
void top_list_sw(t_dir *dir_1, t_dir *dir_2);

