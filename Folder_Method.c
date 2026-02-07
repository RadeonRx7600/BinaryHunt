#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <openssl/sha.h>
#include <sys/stat.h>

//Color System >>
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define RED "\x1b[31m"
#define RESET "\x1b[0m"

//  gcc Folder_Method.c -o Folder_Method -lcrypto

//----------------------------------------------------------------------------------------------------------------

void SHA256test(const char *dir_file1 , const char *dir_file2)
{

    //debugging path ;D u can delete it if u want, or need to creat a feature about it.
    printf("debbuging folder1 sha256 = %s\n",dir_file1);
    printf("debbuging folder2 sha256 = %s\n",dir_file2);
    
    //FUNCTION ___STATUS(OK)___
    
    unsigned char hash1[SHA256_DIGEST_LENGTH];
    unsigned char hash2[SHA256_DIGEST_LENGTH];
    unsigned char buffer[1024];
    size_t lu;

    FILE *f1 = fopen(dir_file1, "rb");
    if (!f1) {
        perror("Error_file_1 : ");
        return;
    }

    FILE *f2 = fopen(dir_file2, "rb");
    if (!f2) {
        perror("Error_file_2 : ");
        return;
    }

    SHA256_CTX ctx1;
    SHA256_Init(&ctx1);
    while ((lu = fread(buffer, 1, sizeof(buffer), f1)) > 0) {
        SHA256_Update(&ctx1, buffer, lu);
    }
    SHA256_Final(hash1, &ctx1);

    SHA256_CTX ctx2;
    SHA256_Init(&ctx2);
    while ((lu = fread(buffer, 1, sizeof(buffer), f2)) > 0) {
        SHA256_Update(&ctx2, buffer, lu);
    }
    SHA256_Final(hash2, &ctx2);

    fclose(f1);
    fclose(f2);


    if (memcmp(hash1, hash2, SHA256_DIGEST_LENGTH) == 0) {
        fprintf(stdout, GREEN "HASH : identical" RESET "\n"); //green
        printf("\n");
    } 
    else {
        fprintf(stdout, RED "HASH : wrong(not the same !)" RESET "\n"); //red
        printf("\n");
    }
}

//----------------------------------------------------------------------------------------------------------------

int check_file(const char *file,const char *folder1, const char *folder2) {

    //FUNCTION __STATUS(OK)__
    
    DIR *dirf2 = opendir(folder2);
    if (!dirf2) {
        return 1;
    }

    struct dirent *entry2;
    
    while ((entry2 = readdir(dirf2)) != NULL) {
        if (strcmp(entry2->d_name, ".") == 0 || strcmp(entry2->d_name, "..") == 0)
            continue;
        
        if (strcmp(file, entry2->d_name) == 0) {
            printf("%sOK : same file >> %s%s\n", GREEN, file, RESET);

            char file_path_folder1[1024];
            char file_path_folder2[1024];

            snprintf(file_path_folder1, sizeof(file_path_folder1), "%s/%s", folder1, file);
            snprintf(file_path_folder2, sizeof(file_path_folder2), "%s/%s", folder2, file);

            SHA256test(file_path_folder1, file_path_folder2);
            
            closedir(dirf2);
            return 1;
        }
    }
    closedir(dirf2);
    return 0;
}

//----------------------------------------------------------------------------------------------------------------

void Pathfinder(const char *folder1 , const char *folder2){

    //FOLDER_FINDING __STATUS__(NOTOK)

    DIR *dirf1 = opendir(folder1);
    if (!dirf1) 
    {
        perror("opendir folder1");
        return 1;
    }
    DIR *dirf2 = opendir(folder2);
    if (!dirf2) 
    {
        perror("opendir folder2");
        return 1;
    }

    struct dirent *entry1;

    char file_path_folder1[1024];
    char file_path_folder2[1024];
    
    struct stat st1,st2;

    while ((entry1 = readdir(dirf1)) != NULL) {

        if (strcmp(entry1->d_name, ".") == 0 || strcmp(entry1->d_name, "..") == 0)
            continue;

        snprintf(file_path_folder1, sizeof(file_path_folder1), "%s/%s", folder1, entry1->d_name);
        snprintf(file_path_folder2, sizeof(file_path_folder2), "%s/%s", folder2, entry1->d_name);

        if (stat(file_path_folder1, &st1) == -1)
            continue;
        
        if (stat(file_path_folder2, &st2) == -1)
            continue;
        
        if (S_ISDIR(st1.st_mode)) {
            //directory (folder)
            Pathfinder(file_path_folder1,file_path_folder2);
        }
            
        else if (S_ISREG(st1.st_mode)) {
            // register(file)
            check_file(entry1->d_name,folder1 ,folder2);
        }
    }

    closedir(dirf1);
    closedir(dirf2);
}

// version 1.0.0 (no bug);
