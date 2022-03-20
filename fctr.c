#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, char *argv[]){
	int num;
	if(argc < 2){
		fprintf(stderr, "This tool creates a series of folders from 01 to n with a given name\nExample: folder_01, folder_02, folder_0n\n");
		fprintf(stderr, "Usage: fctr number_of_folders name_of_folders\n");
		exit(EXIT_FAILURE);
	}
	for(int i = 1; i <= atoi(argv[1]); i++){
		char name[25];
		char buffer[25];
		sprintf(buffer, "_%.2d", i);
		strcpy(name, argv[2]);
		strcat(name, buffer);
		mkdir(name, 0755);
	}
	return 0;
}
