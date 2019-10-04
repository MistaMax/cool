#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/evp.h>
#define MAX_KEY_SIZE 16
#define IV_SIZE 16
#define MAX_INPUT_SIZE 100
#define MAX_CIPHERED_TEXT_LENGTH 100

int encryptText(char *text, int textLength, unsigned char *key, unsigned char *iv, char *output);
void addSpacesToK(unsigned char *k);

int main(int argc, char *argv[]){
    //create file pointer
    FILE *dictionary;
    //unencrypted message
    char inText[] = "This is a top secret.";
    int textLength = 21;
    //encrypted message
    char cipherText[] = "8d20e5056a8d24d0462ce74e4904c1b513e10d1df4a2ef2ad4540fae1ca0aaf9";
    //setting up iv with all zeros
    unsigned char iv[IV_SIZE];
    int i;
    for(i=0;i<IV_SIZE;i++)iv[i]=0;
    //Set up the key with spaces
    unsigned char k[MAX_KEY_SIZE];
    addSpacesToK(k);
    //open the dictionary file
    dictionary = fopen("dictionary.txt","r");
    if(dictionary == NULL){
        printf("ERROR: Openning FIle\n");
        exit(1);
    }
    //loop to pull the dictionary terms and test them as the key
    char inputBuffer[MAX_INPUT_SIZE];
    int keyFound = 0;
    char *output;
    while(fgets(inputBuffer, MAX_INPUT_SIZE, dictionary) != NULL){
        //read in the input buffer from the dictionary to k
        for(i=0;i<MAX_KEY_SIZE;i++){
            if(isprint(inputBuffer[i]) == 0)break;
            if(inputBuffer[i] == ' ')break;
            k[i] = inputBuffer[i];
        }
        //encrypt text file
        encryptText(inText,textLength,k,iv,output);
        //check to see if the output matches the ciphertext
        if(strcmp(output, cipherText) == 0){
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
    for(i=0;i<MAX_KEY_SIZE;i++)k[i]=' ';
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
    //malloc the output
    output = (char *)malloc(MAX_CIPHERED_TEXT_LENGTH);
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
