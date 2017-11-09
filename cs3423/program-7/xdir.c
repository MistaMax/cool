#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
//
void errExit(const char szFmt[], ...);
void listAllFiles(char *szDirName);
void listFileSize(char *szDirName);
void listFiles(char *szDirName);
void listAllFileData(char *szDirName);
//char *concat(const char *s1, const char *s2);
void listFileDataR(char *szDirName, int indent);
void listAllFileDataR(char *szDirName, int indent);
void listAllFilesR(const char *szDirName, int indent);
void listFilesR(const char *szDirName, int indent);
//
int main(int argc, char *argv[])
{
	int i;

	if (argc < 2)
		errExit("Not enough arguments.");

	if (argv[1][0] == '-')
		errExit("Switch should not be the first argument\n");

	if (argc == 2)
		listFiles(argv[1]);
	else
	{
		//
		int l = 0;
		int a = 0;
		int r = 0;
		for (i = 2; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				if (argv[i][1] == 'l')
					l = 1;
				else if (argv[i][1] == 'a')
					a = 1;
				else if (argv[i][1] == 'r')
					r = 1;
				else
					errExit("Invalid command argument");
			}
			else
			{
				errExit("Improper argument");
			}
		}

		//
		if (l)
		{
			if (a){
				if (r)
					listAllFileDataR(argv[1], 4);
				else
					listAllFileData(argv[1]);
			}
			else{
				if (r)
					listFileDataR(argv[1], 4);
				else
					listFileSize(argv[1]);
			}
		}
		else if (a)
		{
			if (r)
				listAllFilesR(argv[1], 4);
			else
				listAllFiles(argv[1]);
		}
		else if (r)
			listFilesR(argv[1], 4);
	}

	return 0;
}

//
void listFiles(char *szDirName)
{
	struct dirent *pDirent;
	struct stat statBuf;

	DIR *pDir;
	pDir = opendir(szDirName);

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s :\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		if (pDirent->d_name[0] != '.')
		{
			printf("    %s\n", pDirent->d_name);
		}
	}
	close(pDir);
}
//
void listAllFiles(char *szDirName)
{
	struct dirent *pDirent;
	struct stat statBuf;

	DIR *pDir;

	pDir = opendir(szDirName);

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s :\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		printf("    %s\n", pDirent->d_name);
	}
	close(pDir);
}
//
void listFileSize(char *szDirName)
{
	struct dirent *pDirent;
	struct stat statBuf;

	DIR *pDir;
	int rc = 0;
	pDir = opendir(szDirName);

	char path[500];

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));
	
	printf("%s:\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

		if (pDirent->d_name[0] != '.')
		{
			if (S_ISDIR(statBuf.st_mode))
			{
				printf("    %s D %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
			}
			if (S_ISREG(statBuf.st_mode))
				printf("    %s F  %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
		}
	}
	close(pDir);
}
//
void listAllFileData(char *szDirName)
{
	struct dirent *pDirent;
	struct stat statBuf;

	DIR *pDir;
	int rc = 0;
	pDir = opendir(szDirName);

	char path[500];

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s:\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

		if (S_ISDIR(statBuf.st_mode))
		{
			printf("    %s D %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
		}
		if (S_ISREG(statBuf.st_mode))
			printf("    %s F  %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
	}
	close(pDir);
}
//
void listFilesR(const char *szDirName, int indent)
{
    DIR *dir;
	struct dirent *pDirent;
	struct stat statBuf;

	int rc = 0;

	if(indent == 4){
		printf("%s:\n",szDirName);
	}

    if (!(dir = opendir(szDirName)))
        return;

    while ((pDirent = readdir(dir)) != NULL) {
		char path[500];
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

        if (S_ISDIR(statBuf.st_mode)) {
            if (pDirent->d_name[0] == '.')
                continue;
            printf("%*s%s:\n", indent, " ", pDirent->d_name);
            listFilesR(path, indent + 4);
        } else {
			if (pDirent->d_name[0] == '.')
				continue;
            printf("%*s%s\n", indent, " ", pDirent->d_name);
        }
    }
    closedir(dir);
}
//
void listAllFilesR(const char *szDirName, int indent)
{
    DIR *dir;
	struct dirent *pDirent;
	struct stat statBuf;

	int rc = 0;

	if(indent == 4){
		printf("%s:\n",szDirName);
	}

    if (!(dir = opendir(szDirName)))
        return;

    while ((pDirent = readdir(dir)) != NULL) {
		char path[500];
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

        if (S_ISDIR(statBuf.st_mode)) {
			if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0){
				printf("%*s%s\n", indent, " ", pDirent->d_name);
				continue;
			}
            printf("%*s%s:\n", indent, " ", pDirent->d_name);
            listAllFilesR(path, indent + 4);
        } else {
            printf("%*s%s\n", indent, " ", pDirent->d_name);
        }
    }
    closedir(dir);
}
//
void listAllFileDataR(char *szDirName, int indent){
    DIR *dir;
	struct dirent *pDirent;
	struct stat statBuf;

	int rc = 0;

	if(indent == 4){
		printf("%s:\n",szDirName);
	}

    if (!(dir = opendir(szDirName)))
        return;

    while ((pDirent = readdir(dir)) != NULL) {
		char path[500];
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

        if (S_ISDIR(statBuf.st_mode)) {
			if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0){
				printf("%*s%s D %ld blks %ld bytes\n", indent, " ", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
				continue;
			}
            printf("%*s%s:\n", indent, " ", pDirent->d_name);
            listAllFileDataR(path, indent + 4);
        } else {
            printf("%*s%s F %ld blks %ld bytes\n", indent, " ", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
        }
    }
    closedir(dir);
}
//
void listFileDataR(char *szDirName, int indent){
	DIR *dir;
	struct dirent *pDirent;
	struct stat statBuf;

	int rc = 0;

	if(indent == 4){
		printf("%s:\n",szDirName);
	}

    if (!(dir = opendir(szDirName)))
        return;

    while ((pDirent = readdir(dir)) != NULL) {
		char path[500];
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

        if (S_ISDIR(statBuf.st_mode)) {
			if (pDirent->d_name[0] == '.')
				continue;
            printf("%*s%s:\n", indent, " ", pDirent->d_name);
            listFileDataR(path, indent + 4);
        } else {
			if (pDirent->d_name[0] == '.')
				continue;
            printf("%*s%s F %ld blks %ld bytes\n", indent, " ", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
        }
    }
    closedir(dir);
}
