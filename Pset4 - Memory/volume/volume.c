// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

// array of bytes to store data from WAV file header
// create place in memory in which to read the file
uint8_t header[HEADER_SIZE];



int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);


    // PART 1) Copy header from input file to output file

    // store data from wav file header in array of bytes -- unit8_t ^^ declared above
    // unit8_t header[HEADER_SIZE];

    // read header bytes from input file
    fread(header, HEADER_SIZE, 1, input);  // read the file into a buffer and then drop the values in the array

    // write header bytes to output file
    fwrite(header, HEADER_SIZE, 1, output); // once we have the info, then we put the manipulated values into the output



    int16_t buffer;  // store audio samples that you read from WAV file
    long buffer_size = sizeof(int16_t);

    // PART 2) Read samples from input file and write updated data to output file
    // read sample bytes from input wav
    while (fread(&buffer, buffer_size, 1, input)) // while reading the file, do these things:
    {

        // multiply sample (stored in buffer) with factor
        buffer *= factor;

        // write new sample to output file
        fwrite(&buffer, buffer_size, 1, output);
    }

    // Close files
    fclose(input);
    fclose(output);
}
