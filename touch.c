#include <sys/types.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <errno.h>
#include <utime.h>
#include <time.h>
#include <errno.h>

#define MODO_CRIACAO S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

#define A_CHANGE_FLAG 1
#define M_CHANGE_FLAG 2

char buffer[80]; // ajuda para usar o sprintf

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

void help(){
	printf("Só é aceito -a e -m como opções.\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
	int i;
	char c;
	int file;
	int change_flags = A_CHANGE_FLAG | M_CHANGE_FLAG;

	opterr = 0;
	while((c = getopt(argc, argv, "am")) != -1){			
		switch(c){		
			case 'a':
				change_flags = A_CHANGE_FLAG;
				break;
			case 'm': 
				change_flags = M_CHANGE_FLAG;
				break;
			default:
			    printf("./touch: Parametro desconhecido: %c\n", optopt);
				printf("---\n");
				help();
		}
	}
	
	if(optind == argc) {
		printf("./touch: falta o operando arquivo\n");
		exit(EXIT_FAILURE);
	}
	
	for(i = optind; i < argc; i++) {
	    char* file_name = argv[i];
	    
	    file = open(file_name, O_CREAT | O_WRONLY, MODO_CRIACAO);
	    if(file == -1) {
	    	sprintf(buffer, "./touch %s", file_name);
	    	perror(buffer);
	    	exit(EXIT_FAILURE);
	    }
	    
	    change_time(file_name, change_flags);
	}
		
	return 0;
}
