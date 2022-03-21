#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>

// PROTOTYPES

void delete_folders(char *num, char *argv_name, int range);
void create_folders(char *num, char *argv_name, int range);
bool is_number(char *num);
char *remove_extension(char a[]);
void folder_matching(void);


// 


int main(int argc, char *argv[]){
	int num;
	int range_min = 1;
	if(argc < 4 && strcmp(argv[1], "-m") != 0 && strcmp(argv[1], "-?") != 0){
		fprintf(stderr, " ----------------------------------------------------------------------\n");
		fprintf(stderr, "| This tool creates a series of folders from 01 to n with a given name |\n");
		fprintf(stderr, "| and can also sort files into folders matching their names.           |\n");
		fprintf(stderr, "| Example: folder_01, folder_02, folder_n                              |\n");
		fprintf(stderr, "| Usage: fctr -flag number_of_folders name_of_folders                  |\n");
		fprintf(stderr, "| Type: 'fctr -?' to see flags                                         |\n");
		fprintf(stderr, " ----------------------------------------------------------------------\n");
		exit(EXIT_FAILURE);
	}
	if(argc == 5){
		if(!is_number(argv[4])){
			fprintf(stderr, "Number of folders invalid!\n");
			exit(EXIT_FAILURE);
		}
		if(atoi(argv[4]) == 0){
			range_min = 1;
		} else{
			range_min = atoi(argv[4]);
		}
	}
	if(argc == 4){
		if(!is_number(argv[2])){
			fprintf(stderr, "Number of folders invalid!\n");
			exit(EXIT_FAILURE);
		}
		if(strlen(argv[3]) > 250){
			fprintf(stderr, "The maximum folder name length is generally 255, this could exceed that\n");
			exit(EXIT_FAILURE);
		}
	}
	if(argv[1][0] != '-'){
		fprintf(stderr, "Flag symbol incorrect; did you forget '-' ?\n");
		exit(EXIT_FAILURE);
	}
	
	switch(argv[1][1]){
		case 'd':
			delete_folders(argv[2], argv[3], range_min);
			break;
		case 'c':
			create_folders(argv[2], argv[3], range_min);
			break;
		case 'm':
			folder_matching();
			break;
		case '?':
			fprintf(stderr, "\nFlags:\n-c\t\tCreates folders.\n-d\t\tDeletes folders.\n-m\t\tMatching mode.\n\n");
			exit(EXIT_FAILURE);
			break;
		default:
			fprintf(stderr, "Unknown flag '%c'\nFlags:\n-c\t\tCreates folders.\n-d\t\tDeletes folders.\n\n", argv[1][1]);
			exit(EXIT_FAILURE);
	}
	return 0;
}

char *remove_extension(char a[]){
	for(int i = 0; i < strlen(a); i++){
		if(a[i] == '.'){
			a[i] = '\0';
			return a;
		}
	}
	return a;
}

void folder_matching(void){
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if(d){
		while((dir = readdir(d)) != NULL){
			char str2[255] = "./";
			char str1[255] = "./";
			char file_name[255];
			char *folder_name;
				strncpy(file_name, dir->d_name, strlen(dir->d_name));
				file_name[strlen(dir->d_name)] = '\0';
				folder_name = remove_extension(dir->d_name);
				mkdir(folder_name, 0755);
				strncat(str2, folder_name, strlen(folder_name));
				strncat(str2, "/", 1);
				strncat(str2, file_name, strlen(file_name));
				strncat(str1, file_name, strlen(file_name));
				printf("%s\n", str1);
				printf("%s\n", str2);
				rename(str1, str2);
			//}
		}
	}
	closedir(d);
	return;
}

void delete_folders(char *num, char *argv_name, int range){
	char name[25];
	char buffer[25];
	int deleted = 0;
	int err;
	for(int i = range; i <= atoi(num); i++){
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

void create_folders(char *num, char *argv_name, int range){
	char name[25];
	char buffer[25];
	int created = 0;
	int err = 0;
	for(int i = range; i <= atoi(num); i++){
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
