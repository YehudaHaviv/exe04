
#include "compress.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int reverseBinary(int num) {
    printf("the number is: %d, ", num);
    int binary[4];
    for (int i = 0; i <= 3; i++) {
        binary[i] = num%2;
        num = (num/2)-(binary[i]/2);
    }
    printf("in binary: ");
    for(int i = 3; i>=0; i--) {
        printf("%d", binary[i]);
    }
    printf(", ");
    for(int i = 0; i<4; i++) {
        if(binary[i]==1) {binary[i] = 0;}
        else {binary[i] = 1;}
    }
    printf("in reverse binary: ");
    for(int i = 3; i>=0; i--) {
    printf("%d", binary[i]);
    }
    printf(", ");
    int ans = 0;
    for (int i = 3; i >= 0; i--) {
        if(binary[i]==1) {
            int j = i;
            int temp = 1;
            while(j>0) {
                temp *= 2;
                j--;
            }
            ans += temp;
        }
    }
    printf("to be saved as: %d\n", ans);
    return ans;
}

void compress_file(FILE *input_file, FILE *output_file) {
    int digit;
    int count = 0;

    while ((digit = fgetc(input_file)) != EOF || !feof(input_file)) {
        int num = digit - '0';
        printf("%d ", num);
        if (num < 0 || num > 9) {
            fprintf(stderr, "Error: Input file contains non-digit characters.\n");
            exit(EXIT_FAILURE);
        }
        int toSave = reverseBinary(num);
        fwrite(&toSave, sizeof(int), 1, output_file);
        count++;
    }

    // Pad with 4 zeros if there is an odd number of digits
    if (count % 2 != 0) {
        int s = 0;
        printf("uneven so wirting: 0000\n");
        fwrite(&s, sizeof(int), 1, output_file);
    }
}

void decompress_file(FILE *input_file, FILE *output_file) {
    int revNum;

    while (fread(&revNum, sizeof(int), 1, input_file) != 0) {
        int ans = reverseBinary(revNum);
        if(ans == 15) {printf("was uneven do not save last number.\n");}
        else if(ans<0||ans>9) {
            fprintf(stderr, "Error: Input file contains non-digit characters.\n");
            exit(EXIT_FAILURE);
        }
        else {fprintf(output_file, "%d", ans);}
    }
}