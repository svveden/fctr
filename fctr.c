#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>

// PROTOTYPES

void delete_folders(char *num, char *argv_name);
void create_folders(char *num, char *argv_name);
bool is_number(char *num);

// 


int main(int argc, char *argv[]){
	int num;
	if(argc < 4){
		fprintf(stderr, " ----------------------------------------------------------------------\n");
		fprintf(stderr, "| This tool creates a series of folders from 01 to n with a given name |\n");
		fprintf(stderr, "| Example: folder_01, folder_02, folder_n                              |\n");
		fprintf(stderr, "| Usage: fctr -flag number_of_folders name_of_folders                  |\n");
		fprintf(stderr, " ----------------------------------------------------------------------\n");
		exit(EXIT_FAILURE);
	}
	if(argv[1][0] != '-'){
		fprintf(stderr, "Flag symbol incorrect; did you forget '-' ?\n");
		exit(EXIT_FAILURE);
	}
	if(!is_number(argv[2])){
		fprintf(stderr, "Number of folders invalid!\n");
		exit(EXIT_FAILURE);
	}
	if(strlen(argv[3]) > 250){
		fprintf(stderr, "The maximum folder name length is generally 255, this could exceed that\n");
		exit(EXIT_FAILURE);
	}
	if(argv[1][1] == 'd'){
		delete_folders(argv[2], argv[3]);
	}
	if(argv[1][1] == 'c'){
		create_folders(argv[2], argv[3]);
	}
	if(argv[1][1] != 'c' && argv[1][1] != 'd'){
		fprintf(stderr, "Unknown flag '%c'\nFlags:\n-c\t\tCreates folders.\n-d\t\tDeletes folders.\n", argv[1][1]);
	}
	return 0;
}

void delete_folders(char *num, char *argv_name){
	char name[25];
	char buffer[25];
	int deleted = 0;
	int err;
	for(int i = 1; i <= atoi(num); i++){
		sprintf(buffer, "_%.2d", i);
		strcpy(name, argv_name);
		strcat(name, buffer);
		if((err = rmdir(name)) == 0){
			deleted++;
		} else if(err < 0 && deleted == 0){
			fprintf(stderr, "No folders could be deleted.\n");
			exit(EXIT_FAILURE);
		} else if(err < 0 && deleted > 0){
			printf("%d folders deleted!\n", deleted);
			return;
		}
	}
	printf("%d folders deleted!\n", deleted);
	return;
}

void create_folders(char *num, char *argv_name){
	char name[25];
	char buffer[25];
	int created = 0;
	int err = 0;
	for(int i = 1; i <= atoi(num); i++){
		sprintf(buffer, "_%.2d", i);
		strcpy(name, argv_name);
		strcat(name, buffer);
	if((err = mkdir(name, 0755)) == 0){
			created++;
		} else if(err == -1){
			fprintf(stderr, "Folder -> %s, already existed, skipping...\n", name);
		}
	}
		printf("%d folders created!\n", created);
		return;
}

bool is_number(char *num){
	if(num[0] == '-'){
			fprintf(stderr, "You can't manipulate NEGATIVE folders, can you?\n");
			exit(EXIT_FAILURE);
	}
	for(int i = 0; i < strlen(num); i++){
		if(isdigit(num[i])){
			i++;
		} else{
			return false;
		}
	} 
	return true;
}
