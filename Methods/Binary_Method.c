#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

int detect () {
  //need to detect if lenght is the same or different function
  
  return 0;
}

int bytes_added (const char *file1, const char *file2) {

    //FUNC __STATUS(~OK)__

    FILE *original_file = fopen(file1, "rb");
    FILE *modified_file = fopen(file2, "rb");
    
    if (!original_file || !modified_file) {
        perror("open error : ");
        return 1;
    }

    unsigned char bytes_original[8192];
    unsigned char bytes_modified[8192];

    size_t register_original_file;
    size_t register_modified_file;
    size_t j = 0;

    while (true) {
        register_original_file = fread(bytes_original, 1, sizeof(bytes_original), original_file);
        register_modified_file = fread(bytes_modified, 1, sizeof(bytes_modified), modified_file);

        if (register_original_file == 0 && register_modified_file == 0) {
            break;
        }

        for (size_t i = 0; i < register_modified_file; i++) {
            if (bytes_original[i] == bytes_modified[j]) {
                j++;
                printf(GREEN"%02X "RESET, bytes_original[i]);
            }
            else {
                while (true) {
                    if(bytes_original[i] != bytes_modified[j]) {
                        printf(RED"%02X "RESET, bytes_modified[j]);
                        j++;
                    }
                    else {   
                        i--;
                        break;
                    }
                }
            }
        }
    }

    fclose(original_file);
    fclose(modified_file);
    printf("\n");
    return 0;
  
}

int main() {

    detect("file1 , file2);

    return 0;
}

//version 1 not finished but had to post it 
