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

#define MODO_CRIACAO S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH

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
			fprintf(stderr,"Erroaaa: %s\n",strerror(errno));
	  		exit(EXIT_FAILURE);
		}	
	}

	while((bytes_lidos=read(file_source,buffer,st.st_size))!=0) 
	   write(file_dest,buffer,bytes_lidos);

	close(file_source);
	close(file_dest);
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
	//Verificar as opções
	while((c = getopt(argc, argv, "am")) != -1){			
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
		copy_file(argv[optind], argv[optind+1]);	
	}
	else{
		struct stat st;
		if((stat(argv[argc-1], &st))==-1){
			printf( "[*] Can't stat() file %s\n", argv[argc-1] );
      		exit(EXIT_FAILURE);
		}
		if (st.st_mode != S_IFDIR){
			printf("./cp: target “%s” is not a directory\n", argv[argc-1]);
			exit(EXIT_FAILURE);
		}
		for (i = optind; i < (argc - 1); i++){
			copy_file(argv[i], argv[argc-1]);
		}		
	}		
	return 0;
}