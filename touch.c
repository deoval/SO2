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

int a_flag = 0;
int m_flag = 0;
char buffer[80]; // ajuda para usar o sprintf

void change_time(char *file_name){
	struct stat fileinfo;
	struct utimbuf _time;
	
	if ( stat( file_name, &fileinfo ) == -1 ){
		sprintf(buffer, "./touch: Can't stat() file %s", file_name);
    	perror(buffer);
      	exit(EXIT_FAILURE);
  	}
   	
	_time.actime = fileinfo.st_atim.tv_sec;
	_time.modtime = fileinfo.st_mtim.tv_sec;
	
	time_t now = time(NULL);
	if(a_flag){
		_time.actime = now;
	}
	
	if(m_flag){
		_time.modtime = now;
	}
	utime(file_name, &_time);
}

void help(){
	printf("Só é aceito -a e -m como opções.\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
	int i;
	char c;
	int file;

	opterr = 0;
	while((c = getopt(argc, argv, "am")) != -1){			
		switch(c){		
			case 'a':
				a_flag = 1;
				break;
			case 'm': 
				m_flag = 1;
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
	    //TO DO Verificar permissões na criação do arquivo
	    file = open(file_name, O_CREAT, MODO_CRIACAO);
	    if(file == -1) {
	    	sprintf(buffer, "./touch %s", file_name);
	    	perror(buffer);
	    	exit(EXIT_FAILURE);
	    }
	    change_time(file_name);
	}
		
	return 0;
}
