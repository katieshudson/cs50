#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{

    // storing block size in variable
    const int BLOCK_SIZE = 512;

    // new type to store a byte of data
    typedef uint8_t BYTE;

    //variable to keep track of # of jpegs found
    int num_jpegs = 0;

    // array of bytes to store data - create place in memory to read the file
    BYTE buffer[BLOCK_SIZE];

    // Check command-line arguments
    if (argc != 2)
    {
        printf("Usage: ./recover card.raw\n");
        return 1;
    }

    // Open memory card
    FILE *input = fopen(argv[1], "r");
    if (input == NULL) // if file cannot be opened, inform the user
    {
        printf("ERROR: Could not open file. Please try again.\n");
        return 1;
    }

    bool inside_jpeg = false;
    char *filename = malloc(8 * sizeof(char));  // need 8 chars because 000.jpg + /nul
    FILE *img = NULL;


    while (fread(buffer, 1, BLOCK_SIZE, input) == BLOCK_SIZE)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && ((buffer[3] & 0xf0) == 0xe0)) // look for header
        {
            if (inside_jpeg) // this closes the previous jpeg since you found a new header
            {
                fclose(img);
                num_jpegs++;
            }

            inside_jpeg = true; // if in header then you are now in a jpeg, so set to true.

            // when inside a jpeg, we write out the jpg
            sprintf(filename, "%03i.jpg", num_jpegs); // created file name

            img = fopen(filename, "w"); // open new jpeg file to write to

            fwrite(buffer, 1, BLOCK_SIZE, img); // we are block aligned, so we write the whole block size

        }
        else
        {
            if (inside_jpeg)
            {
                // keep writing
                fwrite(buffer, 1, BLOCK_SIZE, img); // we are block aligned, so we write the whole block size

            }

            // else ignore this block
        }

    }

    fclose(input); // close the file
    free(filename); // free up memory

}