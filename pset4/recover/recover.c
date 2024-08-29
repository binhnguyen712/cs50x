#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <cs50.h>
int main(int argc, char *argv[])
{
    // check command line argument
    if (argc != 2){
        printf("Usage: ./recover FILE\n");
        return 1;
    }
    //open memory card
    uint8_t buffer[512];
    FILE *mem_card = fopen(argv[1], "r");
    if(mem_card == NULL){
        printf("Could not open file");
        return 2;
    }
   // Create a buffer for a block of data
    int count = 0;
    FILE *img = NULL;
    char *new = malloc(8);
    while(fread(buffer, 1, 512, mem_card) == 512){
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0){
            if (img != NULL){
                fclose(img);
            }
            sprintf(new, "%03i.jpg", count);
            img = fopen(new, "w");
            count++;
        }
        if(img != NULL){
            fwrite(buffer, 1, 512,img);
        }
    }
    free(new);
    fclose(img);
    fclose(mem_card);

}
