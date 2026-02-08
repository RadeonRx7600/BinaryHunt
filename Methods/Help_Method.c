#include <stdio.h>

void helping_method(){  
    
    //FUNCTION __STATUS(OK)__

        printf(">> Here are all the commands : \n");
        printf("\n");
        printf(" -f  --folder  | (Test two folders to see if its identical). | Syntax -> BinaryHunt -f your_folder1 your_folder2\n");
        printf(" -s  --show    | (Standard action of BinaryHunt(by default). | Syntax -> BinaryHunt -s your_file1 your_file2\n");
        printf(" -b  --binary  | (Display the binary modified parts).        | Syntax -> BinaryHunt -b your_file1 your_file2\n");
        printf(" -a  --asembly | (Display the ASM modified parts).           | Syntax -> BinaryHunt -a your_file1 your_file2\n");
        printf(" -h  --help    | (Display the helping commands).             | Syntax -> BinaryHunt -h\n");

}

int main(){

    helping_method();

    return 0;
}