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

void change_time(char *file_name, int access, int modification){
	struct stat fileinfo;
	struct utimbuf _time;
	
	//TO DO Verificar permissões na criação do arquivo
	int file = open(file_name, O_CREAT, S_IRUSR | S_IWOTH);	
	
	if ( (stat( file_name, &fileinfo )) == -1 ){
		//TO-DO tratar melhor isso	
      	printf( "[*] Can't stat() file %s\n", file_name );
      	exit(EXIT_FAILURE);
   	}
   	
	_time.actime = fileinfo.st_atim.tv_sec;
	_time.modtime = fileinfo.st_mtim.tv_sec;
	
	if(access){
		_time.actime = time(NULL);	
	}
	
	if(modification){
		_time.modtime = time(NULL);
	}
	utime(file_name, &_time);
	   	
   //	printf("%lld and %lld", (long long)_time.actime, (long long)fileinfo.st_atim.tv_nsec);
}

void help(){
	printf("Texto para explicar a entrada\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
	int i, c, access = 0, modification = 0, count = 0;

	if (argc < 2 ){
			printf("./touch: falta o operando arquivo\n");
			help();
	}

	while((c = getopt(argc, argv, "am")) != -1){			
		switch(c){			
			case 'a':
				access = 1;
				count = 1;	
				break;	
			case 'm': 
				modification = 1;
				count = 1;
				break;
			default: help(); break;		
		}
	}
	//printf("%s\n", argv[2]);
	if (count == 1)	{
		if(argv[2] == NULL){
			printf("./touch: falta o operando arquivo\n");
			help();
		}
		change_time(argv[2], access, modification);		
	}
	if(count == 0){
		if(argv[1] == NULL){
			printf("./touch: falta o operando arquivo\n");
			help();
		}
		change_time(argv[1], access, modification);	
	}	
}
