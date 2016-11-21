#define _XOPEN_SOURCE 700
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <ftw.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <utime.h>
#include <time.h>
#include "utils.h"

// used by copy
void copy_file(char *source_file_name, char *dest_file_name){
	int file_source, file_dest;
	int bytes_lidos;
	char *buffer;
	struct stat st;

	stat(source_file_name, &st);

	buffer = malloc(st.st_size*sizeof(char));

	file_source = open(source_file_name, O_RDONLY);
	if(file_source == -1){
	    fprintf(stderr,"Erro em source %s: %s\n", source_file_name, strerror(errno));
	    exit(EXIT_FAILURE);
	}

	file_dest = open(dest_file_name,O_WRONLY | O_TRUNC | O_CREAT, st.st_mode);
	if(file_dest == -1){
		char dest_buff[1000] = "";
		strcat(dest_buff, dest_file_name);
		strcat(dest_buff, "/");
		strcat(dest_buff, source_file_name);
		file_dest = open(dest_buff,O_WRONLY | O_TRUNC | O_CREAT, st.st_mode);
		if (file_dest == -1){
			fprintf(stderr,"Erro em dest %s: %s\n",dest_buff, strerror(errno));
	  		exit(EXIT_FAILURE);
		}
	}

	while((bytes_lidos=read(file_source,buffer,st.st_size))!=0)
	   write(file_dest,buffer,bytes_lidos);

	close(file_source);
	close(file_dest);
}
int isnot_dir(char *path){
	struct stat st;
	if((stat(path, &st))==-1){
		printf( "./cp: cannot stat “%s”: %s \n", path, strerror(errno));
  		exit(EXIT_FAILURE);
	}

	if(S_ISDIR(st.st_mode)){
		return 0;
	}
	return 1;

}

void copy_directory_files(char *path, char *dest_file_name){
	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir (path)) != NULL) {
	  /* print all the files and directories within directory */
	  while ((ent = readdir (dir)) != NULL) {
			char file_buff[1000] = "";
			strcat(file_buff, path);
			strcat(file_buff, "/");
			strcat(file_buff, ent->d_name);
			printf("%s\n",dest_file_name );
	    copy_file(file_buff, dest_file_name);
	  }
	  closedir (dir);
	} else {
	  /* could not open directory */
	  printf("cp: impossível obter estado de “%s”: %s\n", path, strerror(errno));
	  exit(EXIT_FAILURE);
	}
}

// used by rm
int rm(const char *file_name)
{
	int res;
	res = remove(file_name);
	if(res){
		printf("Error removing file: %s \n", strerror(errno));
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

//used by cat
char buffer[80]; // ajuda para usar o sprintf

void output_file(char* file_name) {
	int c;
	FILE* file;

	file = fopen(file_name, "r");
    if(file == NULL) {
    	sprintf(buffer, "./cat %s", file_name);
    	perror(buffer);
    	exit(EXIT_FAILURE);
    }

	while ((c = fgetc(file)) != EOF) {
        putchar(c);
	}

	fclose(file);
}

void output_stdin() {
	char c;

	while((c = getchar()) != -1) {
		putchar(c);
	}
}

// used by touch
void change_time(char *file_name, int change_flags){
	struct stat fileinfo;
	struct utimbuf new_time;

	int r_stat = stat( file_name, &fileinfo );
	if ( r_stat == -1 ){
		sprintf(buffer, "./touch: Can't stat() file %s", file_name);
    	perror(buffer);
      	exit(EXIT_FAILURE);
  	}

	new_time.actime = fileinfo.st_atim.tv_sec;
	new_time.modtime = fileinfo.st_mtim.tv_sec;

	time_t now = time(NULL);
	if(change_flags & A_CHANGE_FLAG){
		new_time.actime = now;
	}

	if(change_flags & M_CHANGE_FLAG){
		new_time.modtime = now;
	}

	int r_utime = utime(file_name, &new_time);
	if ( r_utime == -1 ){
		sprintf(buffer, "./touch: Can't change times of file %s", file_name);
    	perror(buffer);
      	exit(EXIT_FAILURE);
  	}
}
