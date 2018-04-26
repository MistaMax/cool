#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

//declaring the functions
void errExit(const char szFmt[], ...);
void listAllFiles(char *szDirName);
void listFileSize(char *szDirName);
void listFiles(char *szDirName);
void listAllFileData(char *szDirName);
void listFileDataR(char *szDirName, int indent);
void listAllFileDataR(char *szDirName, int indent);
void listAllFilesR(const char *szDirName, int indent);
void listFilesR(const char *szDirName, int indent);

//start of the program
int main(int argc, char *argv[])
{
	int i;
	//assures that the ammount of args is correct
	if (argc < 2)
		errExit("Not enough arguments.");

	//runs the main section
	if (argc == 2)
		listFiles(argv[1]); //list the files that are not hidden if the argument just has the directory and the command
	else					//taken if there are more - arguments
	{
		//initializing the variables that determine which route to take
		int l = 0;
		int a = 0;
		int r = 0;
		//starting the loop to read through the args and process them
		for (i = 2; i < argc; i++)
		{
			if (argv[i][0] == '-') //sets variables to 1 if they are found
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

		//executes the appropriate function according to what is following the directory using 1s and 0s
		if (l)
		{
			if (a)
			{
				if (r)
					listAllFileDataR(argv[1], 4);
				else
					listAllFileData(argv[1]);
			}
			else
			{
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

void listFiles(char *szDirName) //list all the non-hidden files
{
	//structures required to read through the directory
	struct dirent *pDirent;
	struct stat statBuf;

	DIR *pDir;
	pDir = opendir(szDirName);

	if (pDir == NULL) //ensures that the directory can be opened
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));
	// prints the initial directory name
	printf("%s :\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL) //reads all the files in the directory
	{
		if (pDirent->d_name[0] != '.')
		{
			printf("    %s\n", pDirent->d_name); //prints the appropriately spaced file name
		}
	}
	close(pDir);
}

void listAllFiles(char *szDirName) //lists hidden and non-hidden files in the directory specified
{
	//structures required to read through the directory
	struct dirent *pDirent;
	struct stat statBuf;

	DIR *pDir;

	pDir = opendir(szDirName);

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s :\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL) //reads each file name
	{
		printf("    %s\n", pDirent->d_name); //prints the name of the file
	}
	close(pDir);
}

void listFileSize(char *szDirName) //lists the data that includes the file size, the blocks, and the type of file it is
{
	//structures required to read through the directory
	struct dirent *pDirent;
	struct stat statBuf;

	DIR *pDir;
	int rc = 0;
	pDir = opendir(szDirName);
	//used as a string to display the full file path
	char path[500];

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s:\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name); //concatnates the file name and the Directory name into path
		rc = stat(path, &statBuf);										   //gets the stats on the file
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

		if (pDirent->d_name[0] != '.')
		{
			if (S_ISDIR(statBuf.st_mode)) //displays the file data, prints D for directory or F for file
			{
				printf("    %s D %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
			}
			if (S_ISREG(statBuf.st_mode))
				printf("    %s F  %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
		}
	}
	close(pDir);
}

void listAllFileData(char *szDirName) //lists all the data for both the file name and the data of it for hidden and non-hidden files
{
	//structures required to read through the directory
	struct dirent *pDirent;
	struct stat statBuf;

	DIR *pDir;
	int rc = 0;
	pDir = opendir(szDirName);
	//used as a string to represent the path
	char path[500];

	if (pDir == NULL)
		errExit("opendir could not open '%s': %s", szDirName, strerror(errno));

	printf("%s:\n", szDirName);
	while ((pDirent = readdir(pDir)) != NULL)
	{
		// getting the data of the file
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

		if (S_ISDIR(statBuf.st_mode)) //Displaying the data of the files
		{
			printf("    %s D %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
		}
		if (S_ISREG(statBuf.st_mode))
			printf("    %s F  %ld blks %ld bytes\n", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
	}
	close(pDir);
}

void listFilesR(const char *szDirName, int indent) //Recurses through all the directories in the set directories and lists all the non-hidden files
{
	DIR *dir;
	struct dirent *pDirent;
	struct stat statBuf;

	int rc = 0;

	if (indent == 4)
	{ //prints the initial directory
		printf("%s:\n", szDirName);
	}

	if (!(dir = opendir(szDirName)))
		return;

	while ((pDirent = readdir(dir)) != NULL)
	{
		char path[500];
		//gets the file data
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}
		//checks to see if it is a directory or not
		if (S_ISDIR(statBuf.st_mode))
		{
			if (pDirent->d_name[0] == '.')
				continue;									  //skips over all hidden files/directories
			printf("%*s%s:\n", indent, " ", pDirent->d_name); //prints the name of the directory after a set ammount of spaces
			listFilesR(path, indent + 4);					  //recursive call to the function if a directory is found
		}
		else
		{
			if (pDirent->d_name[0] == '.')
				continue;									 //skips over all hidden files/directories
			printf("%*s%s\n", indent, " ", pDirent->d_name); //prints the file after a set ammount of spaces
		}
	}
	closedir(dir);
}

void listAllFilesR(const char *szDirName, int indent) //lists all non-hidden and hidden files/directories recursively through all directories inside the given directory
{
	DIR *dir;
	struct dirent *pDirent;
	struct stat statBuf;

	int rc = 0;

	if (indent == 4)
	{ //prints the main Directory name
		printf("%s:\n", szDirName);
	}

	if (!(dir = opendir(szDirName)))
		return;

	while ((pDirent = readdir(dir)) != NULL)
	{
		//gets the data of the current file selected
		char path[500];
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

		if (S_ISDIR(statBuf.st_mode))
		{
			if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)
			{
				printf("%*s%s\n", indent, " ", pDirent->d_name);
				continue;
			}
			printf("%*s%s:\n", indent, " ", pDirent->d_name); //prints the directory after a certain ammount of spaces
			listAllFilesR(path, indent + 4);				  //recursive call that runs if the directory is found
		}
		else
		{
			printf("%*s%s\n", indent, " ", pDirent->d_name); //prints the file after a certain ammount of spaces
		}
	}
	closedir(dir);
}

void listAllFileDataR(char *szDirName, int indent)// list all files and the data with them
{
	//directory scanning variables
	DIR *dir;
	struct dirent *pDirent;
	struct stat statBuf;

	int rc = 0;

	if (indent == 4)
	{
		printf("%s:\n", szDirName);
	}

	if (!(dir = opendir(szDirName)))
		return;

	while ((pDirent = readdir(dir)) != NULL)//reads through the files in a directory
	{
		//making the path to the files
		char path[500];
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

		if (S_ISDIR(statBuf.st_mode))//Checks to see if it is a directory
		{
			if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)
			{
				printf("%*s%s D %ld blks %ld bytes\n", indent, " ", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);//gets the data of the hidden directories
				continue;//jumps to the next increment in the loop
			}
			printf("%*s%s:\n", indent, " ", pDirent->d_name);//prints the directory name after all the spaces
			listAllFileDataR(path, indent + 4);//recurses through the function if it is a directory
		}
		else
		{
			printf("%*s%s F %ld blks %ld bytes\n", indent, " ", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);//prints the file names
		}
	}
	closedir(dir);
}

void listFileDataR(char *szDirName, int indent)
{ //list the file data of all non-hidden files in the directory and subdirectories
	DIR *dir;
	struct dirent *pDirent;
	struct stat statBuf;

	int rc = 0;

	if (indent == 4)//lists the initial name of the directory
	{
		printf("%s:\n", szDirName);
	}

	if (!(dir = opendir(szDirName)))
		return;

	while ((pDirent = readdir(dir)) != NULL)
	{//loops through all the files in the directory
		//creates the path
		char path[500];
		snprintf(path, sizeof(path), "%s/%s", szDirName, pDirent->d_name);
		rc = stat(path, &statBuf);
		if (rc < 0)
		{
			errExit("stat: %s", strerror(errno));
		}

		if (S_ISDIR(statBuf.st_mode))//checks to see if it is a directory
		{
			if (pDirent->d_name[0] == '.')
				continue;
			printf("%*s%s:\n", indent, " ", pDirent->d_name);//prints the directory name then recurses through the rest of the directory
			listFileDataR(path, indent + 4);
		}
		else
		{
			if (pDirent->d_name[0] == '.')
				continue;
			printf("%*s%s F %ld blks %ld bytes\n", indent, " ", pDirent->d_name, statBuf.st_blocks, statBuf.st_size);
		}
	}
	closedir(dir);
}
