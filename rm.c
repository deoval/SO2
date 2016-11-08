#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifndef BUF_SIZE
#define BUF_SIZE 2048
#endif
 
int main(int argc, char *argv[])
{
	char* file_name = argv[1];
	
	if(open(file_name, O_RDONLY, S_IRUSR | S_IWOTH)==-1){
		printf("File do not exist\n");
	}else{
		int res = remove(file_name);
		if(res==-1)
			printf("Error removing file: %s \n", strerror(errno));

	}
	
	return 0;
}
