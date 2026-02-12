#include <stdio.h>

//FUNCTION __STATUS(OK)__

void helping_method(){  
    
        printf(">> Here are all the commands : \n");
        printf("\n");
        printf(" -f  --folder  | (Test two folders to see if its identical). | Syntax -> BinaryHunt -f your_folder1 your_folder2\n");
        printf(" -s  --show    | (Standard action of BinaryHunt(by default). | Syntax -> BinaryHunt -s your_file1 your_file2\n");
        printf(" -b  --binary  | (Display the binary modified parts).        | Syntax -> BinaryHunt -b your_file1 your_file2\n");
        printf(" -a  --asembly | (Display the ASM modified parts).           | Syntax -> BinaryHunt -a your_file1 your_file2\n");
        printf(" -h  --help    | (Display the helping commands).             | Syntax -> BinaryHunt -h\n");

}

void default_status() {

    printf("binaryhunt - binary comparison tool\n\n");
    printf("Usage:\n");
    printf("  binaryhunt -f <folder1> <folder2>   Compare folders\n");
    printf("  binaryhunt -b <file1> <file2>       Compare binaries\n");
    printf("  binaryhunt -h                       Show detailled help\n");
    printf("  binaryhunt -s <file1> <file2>       Future feature\n");
}
