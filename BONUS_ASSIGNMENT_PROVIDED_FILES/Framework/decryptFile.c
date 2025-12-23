/*
 * decryptFile() - Student Implementation Template
 * 
 * Decrypt an encrypted file using XOR cipher with matrix-based key
 * 
 * PARAMETERS:
 *   inputFile  - Encrypted input filename (.bin file)
 *   outputFile - Decrypted output filename (plaintext)
 *   matrix     - 2D decryption key matrix (pre-loaded, same as encryption)
 *   size       - Matrix dimension (2, 3, or 4)
 * 
 * RETURNS:
 *   SUCCESS (1) on successful decryption
 *   FAILURE (0) on any error
 * 
 * REQUIREMENTS:
 *   - Validate all input parameters
 *   - Process file byte-by-byte using fgetc/fputc
 *   - Apply XOR operation with matrix values
 *   - Handle errors and cleanup properly
 * 
 * CRITICAL FILE MODES (⚠️ MANDATORY):
 *   Input:  fopen(inputFile, "rb") - BINARY READ MODE (REQUIRED!)
 *   Output: fopen(outputFile, "w")  - Text write mode
 * 
 *   ⚠️ You MUST use "rb" mode for reading encrypted .bin files!
 *      Encrypted data is binary and must be read in binary mode.
 *      Using "r" mode may corrupt data on some systems.
 * 
 * KEY INSIGHT:
 *   Since (A ⊕ B) ⊕ B = A, applying XOR twice returns original value
 *   This means encryption and decryption use the SAME operation!
 * 
 */

#include "encrypt.h"

int decryptFile(const char* inputFile, const char* outputFile, int** matrix, int size) {
    
    // TODO: Validate input parameters
    // Check for NULL pointers and valid size range
    
    
    // TODO: Open input file for reading (⚠️ BINARY mode "rb")
    // Check if fopen succeeded
    
    
    // TODO: Open output file for writing (text mode)
    // Check if fopen succeeded
    // If it fails, close input file first
    
    
    // TODO: Implement decryption loop
    // - Use fgetc() to read encrypted bytes
    // - Calculate matrix position (same as encryption)
    // - Track byte position (starts at 0, increments each byte)
    // - Apply XOR operation (same as encryption)
    // - Use fputc() to write decrypted bytes
    // - Handle fputc errors
    
    
    //exact same checks as encrypt file, make sure files and matrix are not null
    if (inputFile == NULL || outputFile == NULL || matrix == NULL) {
        return FAILURE;
    }

    //check matrix size
    if (size < MIN_MATRIX_SIZE || size > MAX_MATRIX_SIZE) {
        return FAILURE;
    }

    //opent the files with the correct modes, clean up if neccessary
     FILE *inFile = fopen(inputFile, "rb");   
    if (inFile == NULL) {
        return FAILURE;
    }

    FILE *outFile = fopen(outputFile, "w");  
    if (outFile == NULL) {
        fclose(inFile);
        return FAILURE;
    }

    // prepare variable for decryption and looping
    int ch;
    long long byteIndex = 0;

    while ((ch = fgetc(inFile)) != EOF) { // get the char from file if its not the EOF

        //same indexing, wrap around
        int row = (int)((byteIndex / size) % size);
        int col = (int)(byteIndex % size);

        // XOR is symmetric: (cipher ^ key) = plain
        unsigned char encByte = (unsigned char) ch;
        unsigned char keyByte = (unsigned char) matrix[row][col];
        unsigned char plainByte = encByte ^ keyByte;

        //put the bite in the outfile, cleanup if we reach the EOF
        if (fputc(plainByte, outFile) == EOF) {
            fclose(inFile);
            fclose(outFile);
            return FAILURE;
        }

        byteIndex++;
    }
    //post decryption cleanup
    fclose(inFile);
    fclose(outFile);

    return SUCCESS;
}
