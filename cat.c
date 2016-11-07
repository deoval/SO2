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

int main(int argc, char **argv){
	int i;
	
	if(argc == 1) { // nenhum parametro enviado
		output_stdin();
		exit(0);
	}
	
	for(i = 1; i < argc; i++) {
	    char* file_name = argv[i];
	    
	    if(strcmp("-", file_name) == 0) {
	    	output_stdin();
	    }
	    else {
	    	output_file(file_name);
	    }
	}
		
	return 0;
}
