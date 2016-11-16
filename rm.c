#define _XOPEN_SOURCE 500
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ftw.h>
#define _DEBUGGER
#define MAX_OPEN_DESCRIPTORS 64
int r_flag = 0;
int f_flag = 0;
int err;

int rm(const char *file_name)
{
	int res;
	res = remove(file_name);
	if(res){
		printf("Error removing file: %s \n", strerror(errno));
		err=1;
	}
	return res;
}

int nftw_callback_rm(const char *file_name, const struct stat *sb, int typeflag, struct FTW *ftwbuf)
{
	return rm(file_name);
}

int rmrf(char *path)
{
    return nftw(path, nftw_callback_rm, MAX_OPEN_DESCRIPTORS, FTW_DEPTH | FTW_PHYS);
}

int main(int argc, char *argv[])
{
	char* file_name;
	char c;

	while((c = getopt(argc, argv, "rf")) != -1)
	{
		switch(c){		
			case 'r':
				r_flag = 1;
				break;
			case 'f': 
				f_flag = 1;
				break;
			default:
			    printf("./rm: Unknow Parameter");
				printf("---\n");
		}
	}

	int i;
	for(i = optind; i < argc; i++) {
	    file_name = argv[i];

		if(open(file_name, O_RDONLY, S_IRUSR | S_IWOTH)==-1)
		{
			if (!f_flag) {
				printf("File %s do not exist\n", file_name);
			}
			err=1;
			continue;
		}
	
		if (!r_flag) {
			rm(file_name);
		} else {
			rmrf(file_name);
		}
	}

	#ifdef DEBUGGER
		printf("########## Detailed Log: ##########\n");
		if (err)
		{
			printf("Program exit with error: %s\n",strerror(errno));
		}
		printf("Parameters :\n");
		if (r_flag)
		{
			printf("\t -r: To recursive delete\n");
		}else if (f_flag)
		{
			printf("\t -f: To force delete\n");
		}else {
			printf("\t Default usage of rm\n");
		}
		printf("\t To be deleted: %s \n", file_name);
	#endif
	
	return 0;
}