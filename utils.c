#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <ftw.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <utime.h>
#include <time.h>
#include <errno.h>
#include "utils.h"

void copy_file(char *source_file_name, char *dest_file_name){
	int file_source, file_dest;
	int bytes_lidos;
	char *buffer;
	struct stat st;

	stat(source_file_name, &st);

	buffer = malloc(st.st_size*sizeof(char));

	file_source = open(source_file_name,O_RDONLY, S_IREAD);
	if(file_source == -1){
	    fprintf(stderr,"Erro: %s\n",strerror(errno));
	    exit(EXIT_FAILURE);
	}

	file_dest = open(dest_file_name,O_WRONLY | O_TRUNC | O_CREAT, MODO_CRIACAO);
	if(file_dest == -1){
		char dest_buff[1000] = "";
		strcat(dest_buff, dest_file_name);
		strcat(dest_buff, "/");
		strcat(dest_buff, source_file_name);
		file_dest = open(dest_buff,O_WRONLY | O_TRUNC | O_CREAT, MODO_CRIACAO);
		if (file_dest == -1){
			fprintf(stderr,"Erro: %s\n",strerror(errno));
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