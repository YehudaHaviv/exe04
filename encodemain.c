
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "compress.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s -c/-d filename\n", argv[0]);
        return 1;
    }

    FILE *input_file;
    char *flag = argv[1];
    char *filename = argv[2];
    
    if (strcmp(flag, "-c") == 0) {
        input_file = fopen(filename, "r");
    }
    else {input_file = fopen(filename, "rb");}
    if (input_file == NULL) {
        perror("Error opening input file");
        return 1;
    }

    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) {
        printf("Error: Invalid file format.\n");
        exit(EXIT_FAILURE);
    }

    FILE *output_file;
    char *output_filename;

    if (strcmp(flag, "-c") == 0) {
        output_filename = malloc(strlen(filename) + 5); // 4 characters for ".bin" + null terminator
        if(strcmp(dot + 1, "txt") != 0) {
            printf("Error: file format is not txt\n");
            exit(EXIT_FAILURE);
        }
        strncpy(output_filename, filename, strlen(filename)-4);
        strcat(output_filename, ".bin");
        output_file = fopen(output_filename, "wb");
        if (output_file == NULL) {
            perror("Error opening output file");
            fclose(input_file);
            return 1;
        }
        compress_file(input_file, output_file);
    } else if (strcmp(flag, "-d") == 0) {
        if(strcmp(dot + 1, "bin") != 0) {
            printf("Error: file format is not bin\n");
            exit(EXIT_FAILURE);
        }
        output_filename = malloc(strlen(filename) - 3); // Removing ".bin" extension
        strncpy(output_filename, filename, strlen(filename) - 4); // Copying all but the last 4 characters
        strcat(output_filename, ".txt");
        output_file = fopen(output_filename, "w");
        if (output_file == NULL) {
            perror("Error opening output file");
            fclose(input_file);
            return 1;
        }
        decompress_file(input_file, output_file);
    } else {
        fprintf(stderr, "Invalid flag specified\n");
        fclose(input_file);
        return 1;
    }

    fclose(input_file);
    fclose(output_file);

    free(output_filename);

    return 0;
}
