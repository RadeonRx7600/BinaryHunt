#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// BinaryHunt is a tool to analyse modified file to their original;
// It compares binary and turn it into a ASM code or binary;
// started at : 3pm; 28/01/2026;
// Github >> https://github.com/RadeonRx7600
// MIT LICENSE >> https://opensource.org/license/mit ...soon

int main(int argc, char **argv)  //  gcc -Wall -Wextra main.c Methods/*.c -o binaryhunt -lcrypto
{
    int opt;
    int optind;

    if (argc < 2) {
        default_status();
        return EXIT_FAILURE;
    }

    while ((opt = getopt(argc, argv, "fbh")) != -1) {
        switch (opt) {

        case 'f':
            if (optind + 1 >= argc) {
                fprintf(stderr, "binaryhunt -f requires two folders\n");
                return EXIT_FAILURE;
            }
            Pathfinder(argv[optind], argv[optind + 1]);
            return EXIT_SUCCESS;

        case 'b':
            if (optind + 1 >= argc) {
                fprintf(stderr, "binaryhunt -b requires two files\n");
                return EXIT_FAILURE;
            }
            detect(argv[optind], argv[optind + 1]);
            return EXIT_SUCCESS;

        case 'h':
            helping_method();
            return EXIT_SUCCESS;
            
        default:
            default_status();
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}
