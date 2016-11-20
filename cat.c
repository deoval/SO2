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
