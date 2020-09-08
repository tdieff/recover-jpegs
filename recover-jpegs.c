// Recover JPEGS from a forensic image 'forensic_img.raw'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
	// Enforce usage: single command-line argument w forensic image file name
	if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // If forensic image cannot be opened for reading, inform user and exit
    if (strncmp(argv[1], "forensic_img.raw", 8) != 0)
    {
        printf("Forensic image cannot be opened for for reading\n");
        return 1;
    }

    // Open forensic image for reading
    FILE *forensic_img = fopen(argv[1], "r");
    if (forensic_img == NULL)
    {
        printf("Memory allocation failed\n");
        return 1;
    }

	// Allocate memory for 512 byte buffer 
	BYTE *buffer = malloc(512);
    char *jpeg_content_block = malloc(512);
    FILE *jpeg_file;

    // Read 512 bytes at a time from forensic_img into a array of bytes 'buffer'
    fread(buffer, 1, 512, forensic_img);

	// Count number of JPEGs recovered from forensic image and written to .jpg 
	int recovered_jpeg_count = 0;

    // Loop through entire forensic_img 512 bytes at a time (one 'memory card' block)
    while (fread(buffer, 1, 512, forensic_img) == 512)
    {
		// Check for JPEG signature        
		if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Create and name new empty JPEG file
            sprintf(jpeg_content_block, "%03i.jpg", recovered_jpeg_count);

            // Open new JPEG file to write JPEG content into
            jpeg_file = fopen(jpeg_content_block, "w");

            // Write buffer contents into JPEG file, increment counter, close
            fwrite(buffer, 1, 512, jpeg_file);
            recovered_jpeg_count++;
            fclose(jpeg_file);
        }
        else if (recovered_jpeg_count > 0)
        {
			// Append existing partial jpeg file with additional block         
			jpeg_file = fopen(jpeg_content_block, "a");
            fwrite(buffer, 1, 512, jpeg_file);
            fclose(jpeg_file);
        }
    }

	// Close file forensic image stream and free memory
    fclose(forensic_img);
    free(jpeg_content_block);
    free(buffer);
    return 0;
}
