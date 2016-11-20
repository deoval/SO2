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
	printf("Esse programa não aceita opções.\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
	int i;
	char c;

	opterr = 0;
	// Verificar as opções
	while((c = getopt(argc, argv, "")) != -1){			
		switch(c){		
			case 'a':
				//a_flag = 1;
				break;
			case 'm': 
				//m_flag = 1;
				break;
			default:
			    printf("./cp: Parametro desconhecido: %c\n", optopt);
				printf("---\n");
				help();
		}
	}

	if(optind == argc) {
		printf("./cp: falta o operando arquivo\n");
		exit(EXIT_FAILURE);
	}
	if((optind+1) == argc) {
		printf("./cp: falta o operando arquivo de destino após “%s”\n", argv[optind]);
		exit(EXIT_FAILURE);
	}

	if ((optind+2) == argc){
		if (isnot_dir(argv[optind])){			
			copy_file(argv[optind], argv[optind+1]);	
		}
		else{
			printf("./cp: omitting directory “%s”\n", argv[optind]);
		}
	}
	else{		
		if (isnot_dir(argv[argc-1])){
			printf("./cp: target “%s” is not a directory\n", argv[argc-1]);
			exit(EXIT_FAILURE);
		}
		for (i = optind; i < (argc - 1); i++){
			if (isnot_dir(argv[i])){
				copy_file(argv[i], argv[argc-1]);				
			}
			else{
				printf("./cp: omitting directory “%s”\n", argv[i]);
			}
		}		
	}		
	return 0;
}