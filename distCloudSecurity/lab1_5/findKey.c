#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#define MAX_KEY_SIZE 16
#define IV_SIZE 16
#define MAX_INPUT_SIZE 100
#define MAX_CIPHERED_TEXT_LENGTH 33

int handleErrors();
int encryptText(char *text, int textLength, unsigned char *key, unsigned char *iv, char *output);
void addSpacesToK(unsigned char *k);

int main(int argc, char *argv[]){
    //create file pointer
    FILE *dictionary;
    //unencrypted message
    char inText[] = "This is a top secret.";
    int textLength = 21;
    //encrypted message
    char cipherText[] = "8D20E5056A8D24D0462CE74E4904C1B513E10D1DF4A2EF2AD4540FAE1CA0AAF9";
	//capitalize the cipherTextHex values
	/*char *cipherText = cipherTextHex;
  	while (*cipherText) {
    	*cipherText = toupper((unsigned char) *cipherText);
    	cipherText++;
  	}*/
	int i;
    //setting up iv with all zeros
    unsigned char iv[IV_SIZE+1];
    for(i=0;i<IV_SIZE;i++)iv[i]=0;
	iv[IV_SIZE] = '\0';
    //Set up the key with spaces
    unsigned char k[MAX_KEY_SIZE+1];
	k[MAX_KEY_SIZE] = '\0';
    addSpacesToK(k);
    //open the dictionary file
    dictionary = fopen("dictionary.txt","r");
    if(dictionary == NULL){
        printf("ERROR: Openning FIle\n");
        exit(1);
    }
    
    //loop to pull the dictionary terms and test them as the key
    char szInputBuffer[MAX_INPUT_SIZE];
    int keyFound = 0;
    char *output;
    printf("initialization done\nstarting loop\n");
    while(fgets(szInputBuffer, MAX_INPUT_SIZE, dictionary) != NULL){
        output = (char *)malloc(MAX_CIPHERED_TEXT_LENGTH);
        printf("starting to load data into key:%s\n",szInputBuffer);
        //read in the input buffer from the dictionary to k
        for(i=0;i<MAX_KEY_SIZE;i++){
            if(isprint(szInputBuffer[i]) == 0)break;
            if(szInputBuffer[i] == ' ')break;
            k[i] = szInputBuffer[i];
        }
        printf("\tk:");
        for(i=0;i<MAX_KEY_SIZE;i++){
            if(k[i] == ' ')printf("|S|");
            else printf("%c",k[i]);
        }
        printf("\n");
        //encrypt text file
        int cipherTextLength = encryptText(inText,textLength,k,iv,output);
		printf("\tEncrypted output: %s\n\tLength:%d\n",output, cipherTextLength);
		char convertedOutput[cipherTextLength*2 + 1];
		//convert the ascii character to hex
		int convI = 0;
		for(i = 0;i<cipherTextLength;i++){
			sprintf((char *)(convertedOutput+convI),"%02X",output[i]);
			convI+=2;
		}
		convertedOutput[cipherTextLength*2] = '\0';
		printf("\tConverted Text: %s\n\n",convertedOutput);
        //check to see if the output matches the ciphertext
        if(strcmp(convertedOutput, cipherText) == 0){
            keyFound = 1;
            free(output);
            break;
        }
        free(output);
        addSpacesToK(k);
    }
    if(keyFound == 1){
        printf("The key is:\n%s\n",k);
    }
    fclose(dictionary);
    return 0;
}


void addSpacesToK(unsigned char *k){
    int i;
    for(i=0;i<MAX_KEY_SIZE;i++)k[i]=0x20;
}

int encryptText(char *text, int textLength, unsigned char *key, unsigned char *iv, char *output){
    EVP_CIPHER_CTX *ctx;

    int len;

    int ciphertext_len;

    /* Create and initialise the context */
    if(!(ctx = EVP_CIPHER_CTX_new()))handleErrors();

    /*
     * Initialise the encryption operation. IMPORTANT - ensure you use a key
     * and IV size appropriate for your cipher
     * In this example we are using 256 bit AES (i.e. a 256 bit key). The
     * IV size for *most* modes is the same as the block size. For AES this
     * is 128 bits
     */
    if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_128_cbc(), NULL, key, iv))handleErrors();
    
    /*
     * Provide the message to be encrypted, and obtain the encrypted output.
     * EVP_EncryptUpdate can be called multiple times if necessary
     */
    if(1 != EVP_EncryptUpdate(ctx, output, &len, text, textLength))handleErrors();
    
    ciphertext_len = len;

    /*
     * Finalise the encryption. Further ciphertext bytes may be written at
     * this stage.
     */
    if(1 != EVP_EncryptFinal_ex(ctx, output + len, &len))
        handleErrors();
    ciphertext_len += len;

    /* Clean up */
    EVP_CIPHER_CTX_free(ctx);

    return ciphertext_len;
}

int handleErrors(){
	printf("ERROR: FOUND ERROR IN ENCRYPTION!!!!\n");
    return 1;
}
