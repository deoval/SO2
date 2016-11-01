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

/*int main(int argc, char **argv){
	int i = 0;

	// defaults quando nenhuma opção é enviada
	//char option = 'r';
	//int argument_index_of_first_directory_path = 1;
	
	int result;
	int number_of_options = 0;
	//opterr = 0; // esconde os prints para stderr quando acha um parametro desconhecido
	while((result = getopt(argc, argv, "+rdlbc")) != -1){
		number_of_options++;
		
		if(result == '?') {
			printf("Opção %c inválida. Só as opções r,d,l,b,c são permitidas.\n", optopt);
			return -1;
		}
		if(number_of_options > 1) {
			printf("Só deve ser enviada uma unica opção no máximo!\n");
			return -1;
		}
		
		option = result;
		argument_index_of_first_directory_path = 2;
	}
	opterr = 1;
	
	printf("Option used: %c\n", option);
	
	printf("Directories:\n");
	
	if(argument_index_of_first_directory_path == argc){
		scan_directory(".", option);
	}
	
	for(i = argument_index_of_first_directory_path; i < argc; i++) {
		scan_directory(argv[i], option);
	}

	return 0;
}*/
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
}

int main(int argc, char **argv){
	int i, c, access = 0, modification = 0;
	while((c = getopt(argc, argv, "am")) != -1){			
		switch(c){			
			case 'a':
				access = 1;	
				break;	
			case 'm': 
				modification = 1;
				break;
			default: help(); break;		
		}
	}
	
	change_time(argv[2], access, modification);
	
}
