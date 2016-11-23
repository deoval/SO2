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
	printf("Só é aceito -r como opção.\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char **argv){
	int i, r_flag=0;
	char c;

	opterr = 0;
	// Verificar as opções
	while((c = getopt(argc, argv, "r")) != -1){
		switch(c){
			case 'r':
				r_flag = 1;
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
			if (strcmp(argv[optind], argv[optind+1]) == 0) {
				printf("./cp: “%s” and “%s” are the same file\n", argv[optind], argv[optind+1]);
			}
			else{
				copy_file(argv[optind], argv[optind+1]);
			}
		}
		else{
			if (r_flag) {
				if (strcmp(argv[optind], argv[optind+1]) == 0) {
					printf("./cp: cannot copy a directory, “%s”, into itself, “%s/%s”\n", argv[optind], argv[optind+1], argv[optind]);
				}
				else{
					copy_directory_files(argv[optind], argv[optind+1]);
				}
			}
			else{
				printf("./cp: omitting directory “%s”\n", argv[optind]);
			}
		}
	}
	else{
		if (isnot_dir(argv[argc-1])){
			printf("./cp: target “%s” is not a directory\n", argv[argc-1]);
			exit(EXIT_FAILURE);
		}
		for (i = optind; i < (argc - 1); i++){
			if (isnot_dir(argv[i])){
				if (strcmp(argv[i], argv[argc-1]) == 0) {
					printf("./cp: “%s” and “%s” are the same file\n", argv[i], argv[argc-1]);
				}
				else{
					copy_file(argv[i], argv[argc-1]);
				}
			}
			else{
				if (r_flag) {
					if (strcmp(argv[i], argv[argc-1]) == 0) {
						printf("./cp: cannot copy a directory, “%s”, into itself, “%s/%s”\n", argv[i], argv[argc-1], argv[i]);
					}
					else{
						copy_directory_files(argv[i], argv[argc-1]);
					}
				}
				else{
					printf("./cp: omitting directory “%s”\n", argv[i]);
				}
			}
		}
	}
	return 0;
}
