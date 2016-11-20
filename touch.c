#define _XOPEN_SOURCE 700
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
#include "utils.h"

void help(){
	printf("Só é aceito -a e -m como opções.\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
	int i;
	char c;
	char buffer[80];
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
