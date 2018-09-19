#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cs3743p2.h"

/**********************************************************************************************
 * Author: Max Crookshanks
 * Purpose: Create a data file containing certain record entries for movies
 *********************************************************************************************/
/*hashCreate
This creates a hash header file with the designated filename, and using the current hash header.
This returns a code to ensure everything went fine or if the file already exists
*/
int hashCreate(char szFileNm[], HashHeader *pHashHeader)
{
    FILE *pHashFile;
    //opens a file with read to see if it exists
    if (fopen(szFileNm, "rb") != NULL)
        return RC_FILE_EXISTS;
    //creates and opens a file
    pHashFile = fopen(szFileNm, "wb");
    //sets the high overflow RBN to the primary number
    pHashHeader->iHighOverflowRBN = pHashHeader->iNumPrimary;
    //writes the hash header to the desired file name
    fwrite(pHashHeader, sizeof(HashHeader), 1L, pHashFile);
    //closes the file
    fclose(pHashFile);

    return RC_OK;
}
/**
 * hashOpen
 * 
 * Opens a file containing the hashed data
 */
int hashOpen(char szFileNm[], HashFile *pHashFile)
{
    //uses rb+ to read and write to a binary file
    pHashFile->pFile = fopen(szFileNm, "rb+");
    //checks to see if the file exists
    if (pHashFile->pFile == NULL)
        return RC_FILE_NOT_FOUND;
    //reads in the hash header from the data file to the pHashFile->hashHeader
    if (fread(&(pHashFile->hashHeader), sizeof(HashHeader), 1L, pHashFile->pFile) == 0)
        return RC_HEADER_NOT_FOUND;
    //returns RC_OK if everything worked
    return RC_OK;
}
/**
 * readRec
 * 
 * Reads in a record at a specified iRBN from the data file
 */
int readRec(HashFile *pHashFile, int iRBN, void *pRecord)
{
    long lRBA = 0;
    lRBA = iRBN * pHashFile->hashHeader.iRecSize;
    //goes to the desired location at lRBA
    fseek(pHashFile->pFile, lRBA, SEEK_SET);
    //reads the data from the data file, returns RC_LOC_NOT_FOUND if the location does not exist
    if (fread(pRecord, pHashFile->hashHeader.iRecSize, 1L, pHashFile->pFile) != 1)
        return RC_LOC_NOT_FOUND;

    return RC_OK;
}
/**
 * writeRec
 * 
 * writes the record at the specified iRBN to the data file
 */
int writeRec(HashFile *pHashFile, int iRBN, void *pRecord)
{
    long lRBA = 0;
    lRBA = iRBN * pHashFile->hashHeader.iRecSize;
    //goes to the desired location at lRBA
    fseek(pHashFile->pFile, lRBA, SEEK_SET);
    //writes the record to the data file, returns RC_LOC_NOT_WRITTEN if it failed to write
    if (fwrite(pRecord, pHashFile->hashHeader.iRecSize, 1L, pHashFile->pFile) != 1)
        return RC_LOC_NOT_WRITTEN;

    return RC_OK;
}
/**
 * movieInsert
 * 
 * Inserts a movie record into the data file according to its hash value
 * 
 */
int movieInsert(HashFile *pHashFile, Movie *pMovie)
{
    int iRBN = 0;
    iRBN = hash(pMovie->szMovieId, pHashFile->hashHeader.iNumPrimary);
    //Creating a variable pCursor that scans through the data file to see if a space is open
    Movie *pCursor = (Movie *)malloc(sizeof(Movie));
    //checks to see if the space is open at iRBN
    if (readRec(pHashFile, iRBN, pCursor) == RC_LOC_NOT_FOUND)
    {
        pMovie->iNextChain = 0;
        writeRec(pHashFile, iRBN, pMovie);
        free(pCursor);
        return RC_OK;
    }
    else if (pCursor->szMovieId[0] == '\0')
    {
        pMovie->iNextChain = 0;
        writeRec(pHashFile, iRBN, pMovie);
        free(pCursor);
        return RC_OK;
    }
    else if (strcmp(pCursor->szMovieId, pMovie->szMovieId) == 0) //if there is already the same movie at that location, return RC_REC_EXISTS
    {
        free(pCursor);
        return RC_REC_EXISTS;
    }
    //returns RC_SYNONYM if there is already a file at that hash location that is not the same movie entry
    int count = 0;
    while (pCursor->iNextChain)
    {
        count++;
        if (readRec(pHashFile, pCursor->iNextChain, pCursor) == RC_LOC_NOT_FOUND)
            break;
        else if (pCursor->szMovieId[0] == '\0')
            break;
        else if (strcmp(pCursor->szMovieId, pMovie->szMovieId) == 0) //if there is already the same movie at that location, return RC_REC_EXISTS
        {
            free(pCursor);
            return RC_REC_EXISTS;
        }
    }
    iRBN += count * (pHashFile->hashHeader.iNumPrimary);
    pCursor->iNextChain = iRBN;
    movieUpdate(pHashFile, pCursor);
    free(pCursor);
    writeRec(pHashFile, iRBN, pMovie);
    return RC_OK;
}
/**
 * movieRead
 * Reads a movie according to its hash value in the data file
 */
int movieRead(HashFile *pHashFile, Movie *pMovie, int *piRBN)
{
    int iRBN = hash(pMovie->szMovieId, pHashFile->hashHeader.iNumPrimary);
    Movie *pCursor = (Movie *)malloc(sizeof(Movie));
    readRec(pHashFile, iRBN, pCursor);
    //Reads in a movie into pMovie from the datafile
    if (strcmp(pCursor->szMovieId, pMovie->szMovieId) == 0)
    {
        memcpy(pMovie, pCursor, sizeof(Movie));
        free(pCursor);
        return RC_OK;
    }
    else
    {
        free(pCursor);
        return RC_REC_NOT_FOUND;
    }
}

int movieUpdate(HashFile *pHashFile, Movie *pMovie)
{

}

int movieDelete(HashFile *pHashFile, Movie *pMovie)
{
    return RC_NOT_IMPLEMENTED;
}