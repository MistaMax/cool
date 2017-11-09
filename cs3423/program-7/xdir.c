#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

void errExit(const char szFmt[], ...);
void processCommandSwitches(int argc, char *argv[], struct dirent *pDirent, struct stat statBuf);
void listAllFiles(char *szDirName, struct dirent *pDirent, struct stat statBuf);
void listFileSize(char *szDirName, struct dirent *pDirent, struct stat statBuf);
void listFiles(char *szDirName, struct dirent *pDirent, struct stat statBuf);
void listAllFileData(char *szDirName, struct dirent *pDirent, struct stat statBuf);
char *concat(const char *s1, const char *s2);

//
int main(int argc, char *argv[])
{
	struct dirent *pDirent;
	struct stat statBuf;

	processCommandSwitches(argc, argv, pDirent, statBuf);

	return 0;
}
//
void listFiles(char *szDirName, struct dirent *pDirent, struct stat statBuf)
{
	DIR *pDir;

	pDir = opendir(szDirName);

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s :\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		if (pDirent->d_name[0] != '.')
		{
			printf("\t%s\n", pDirent->d_name);
		}
	}
	close(pDir);
}
//
void listAllFiles(char *szDirName, struct dirent *pDirent, struct stat statBuf)
{
	DIR *pDir;

	pDir = opendir(szDirName);

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s :\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		printf("\t%s\n", pDirent->d_name);
	}
	close(pDir);
}
//
void listFileSize(char *szDirName, struct dirent *pDirent, struct stat statBuf)
{
	DIR *pDir;
	int rc = 0;
	pDir = opendir(szDirName);

	char *szTmp;

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s:\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		szTmp = concat(szDirName, "/");
		szTmp = concat(szTmp, pDirent->d_name);
		rc = stat(szTmp, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

		if (pDirent->d_name[0] != '.')
		{
			if (S_ISDIR(statBuf.st_mode))
			{
				printf("\t%s D %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
			}
			if (S_ISREG(statBuf.st_mode))
				printf("\t%s F  %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
		}
	}
	close(pDir);
}
//
void listAllFileData(char *szDirName, struct dirent *pDirent, struct stat statBuf)
{
	DIR *pDir;
	int rc = 0;
	pDir = opendir(szDirName);

	char *szTmp;

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s:\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		szTmp = concat(szDirName, "/");
		szTmp = concat(szTmp, pDirent->d_name);
		rc = stat(szTmp, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

		if (S_ISDIR(statBuf.st_mode))
		{
			printf("\t%s D %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
		}
		if (S_ISREG(statBuf.st_mode))
			printf("\t%s F  %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
	}
	close(pDir);
}
//
void processCommandSwitches(int argc, char *argv[], struct dirent *pDirent, struct stat statBuf)
{
	int i;

	if (argc < 2)
		errExit("Not enough arguments.");

	if (argv[1][0] == '-')
		errExit("Switch should not be the first argument\n");

	if (argc == 2)
	{
		listFiles(argv[1], pDirent, statBuf);
	}
	else if (argc == 3)
	{
		//
		if (argv[2][0] == '-')
		{
			if (argv[2][1] == 'l')
			{
				listFileSize(argv[1], pDirent, statBuf);
			}
			else if (argv[2][1] == 'a')
			{
				listAllFiles(argv[1], pDirent, statBuf);
			}
		}
	}
	else
	{
		//
		int l = 0;
		int a = 0;
		for (i = 2; i < argc; i++)
		{
			if (argv[i][0] == '-')
			{
				if (argv[i][1] == 'l')
				{
					l = 1;
				}
				else if (argv[i][1] == 'a')
				{
					a = 1;
				}
			}
		}
		//
		if (l == 1)
		{
			if (a == 1)
			{
				listAllFileData(argv[1], pDirent, statBuf);
			}
			else
			{
				listFileSize(argv[1], pDirent, statBuf);
			}
		}
		else
		{
			if (a == 1)
			{
				listAllFiles(argv[1], pDirent, statBuf);
			}
		}
	}
}

char *concat(const char *s1, const char *s2)
{
	char *result = malloc(strlen(s1) + strlen(s2) + 1); //+1 for the null-terminator
	if (result == NULL)
	{
		errExit("Malloc Failed");
	}
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}