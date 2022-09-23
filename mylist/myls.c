#include "secret_headers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

char* pathcat(const char* str1, char* str2) {
	char* res;
	size_t strlen1 = strlen(str1);
	size_t strlen2 = strlen(str2);
	int i, j;
	res = malloc(strlen1+strlen2+2);
	strcpy(res, str1);
	res[strlen1] = '/';
	for (i = strlen1+1, j = 0; ((i<(strlen1+strlen2+1)) && (j<strlen2)); i++, j++)
		res[i] = str2[j];
	res[strlen1+strlen2+1] = '\0';
	return res;
}

void ls(int i, int l, int R, char* path) {
	//printf("open %s\n", path);
	DIR *dp = opendir(path);
	struct stat fileStat;
	if (!dp) {
		printf("It is a file\n");
		stat(path, &fileStat);
		struct passwd *pw = getpwuid(fileStat.st_uid);
		struct group *grp = getgrgid(fileStat.st_gid);
		struct timespec st_mtim = fileStat.st_mtim;
		if (i == 1) {
			printf("%ld ", fileStat.st_ino);
		}
		if (l == 1) {
			printf("%ld ", fileStat.st_nlink);
			printf("%s ", pw->pw_name);
			printf("%s ", grp->gr_name);
			printf("%6ld ", fileStat.st_size);
			time_t tv_sec = st_mtim.tv_sec;
			char buff[100];
			strftime(buff, sizeof buff, "%b %d %Y %H:%M", gmtime(&tv_sec));
			printf("%s ", buff);
		}
		printf("%s\n", path);
		return;
	}
	//printf("not a file\n");
	struct dirent* d;
	while (d = readdir(dp)) {
		//printf("look at %s\n", d->d_name);
		//printf("%ld %d %d %s\n", d->d_ino, d->d_reclen, d->d_type, d->d_name);		
		if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0)
			continue;	
		char* fullName = pathcat(path, d->d_name);
		//printf("fullName: %s\n", fullName);
		stat(fullName, &fileStat);
		//printf("Information for %s\n",d->d_name);
		//printf("---------------------------\n");
		//printf("File Size: \t\t%ld bytes\n",fileStat.st_size);
		//printf("Number of Links: \t%ld\n",fileStat.st_nlink);
		//printf("File inode: \t\t%ld\n",fileStat.st_ino);
		//printf("User ID: %u\n",fileStat.st_uid);
		struct passwd *pw = getpwuid(fileStat.st_uid);
		//printf("Group ID: %u\n",fileStat.st_gid);
		struct group *grp = getgrgid(fileStat.st_gid);
		struct timespec st_mtim = fileStat.st_mtim;
		if (i == 1) {
			printf("%ld ", d->d_ino);
		}
		if (l == 1) {
			printf("%ld ", fileStat.st_nlink);
			printf("%s ", pw->pw_name);
			printf("%s ", grp->gr_name);
			printf("%6ld ", fileStat.st_size);
			time_t tv_sec = st_mtim.tv_sec;
			char buff[100];
			strftime(buff, sizeof buff, "%b %d %Y %H:%M", gmtime(&tv_sec));
			printf("%s ", buff);
		}
		printf("%s\n", d->d_name);
		if (R == 1 && (fileStat.st_mode & S_IFMT) == S_IFDIR) {
			ls(i, l, R, fullName);
		}
	}
	closedir(dp); // close the handle (pointer)
}

int main(int argc, char **argv)
{
	char *path;
	char *option = NULL;
	int i = 0, l = 0, R = 0, fileIndex = 0;
	if (argc == 1)
		fileIndex = 1;
	else {
		char * secondArg = argv[1];
		if (secondArg[0] == '-') {
			option = argv[1];
			fileIndex = 2;
		} else {
			fileIndex = 1;
		}
	}

	if (option) {
		//printf("option: %s\n", option);
		for (int ind = 1; ind < strlen(option); ind++) {
			if (option[ind] == 'i' || option[ind] == 'I')
				i = 1;
			else if (option[ind] == 'l' || option[ind] == 'L')
				l = 1;
			else if (option[ind] == 'R' || option[ind] == 'r')
				R = 1;
			else {
				printf("Error : Unsupported Option\n");
				return 1;
			}
		}
	}
	//printf("i: %d l: %d R: %d fileIndex: %d\n", i, l, R, fileIndex);

	if (fileIndex == argc) {
		ls(i, l, R, ".");
	} else {
		for (int j = fileIndex; j < argc; j++) {
			path = argv[j];
			ls(i, l, R, path);
		}
	}
	return 0;
}

