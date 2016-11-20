#include <ftw.h>
#include <sys/stat.h>
#define MODO_CRIACAO S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH

// used by cp
void copy_file(char *source_file_name, char *dest_file_name);
int isnot_dir(char *path);

//used by rm
#define MAX_OPEN_DESCRIPTORS 64
int rm(const char *file_name);
int nftw_callback_rm(const char *file_name, const struct stat *sb, int typeflag, struct FTW *ftwbuf);
int rmrf(char *path);

// used by cat
void output_file(char* file_name);
void output_stdin();

// used by touch
#define A_CHANGE_FLAG 1
#define M_CHANGE_FLAG 2

void change_time(char *file_name, int change_flags);