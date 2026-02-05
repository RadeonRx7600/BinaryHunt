#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sys/stat.h>

void SHA256test(const char *dir_file1 , const char *dir_file2)
{
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
        printf(stdout,"\x1b[32mHASH : same\x1bn[0m\n");//green
    } 
    else {
        printf(stdout,"\x1b[31mHASH : not the same\x1bn[0m\n");//red
    }
}

//----------------------------------------------------------------------------------------------------------------

int check_file(const char *file, const char *folder2) {
    DIR *dirf2 = opendir(folder2);
    if (!dirf2) return 0;

    struct dirent *entry2;
    while ((entry2 = readdir(dirf2)) != NULL) {
        if (strcmp(entry2->d_name, ".") == 0 || strcmp(entry2->d_name, "..") == 0)
            continue;
        if (strcmp(file, entry2->d_name) == 0) {
            printf("same file is %s\n", file);
            closedir(dirf2);
            return 1;
        }
    }
    closedir(dirf2);
    return 0;
}

void Pathfinder(const char *folder1 , const char *folder2)
//FOLDER_FINDING __STATUS__(NOTOK)
{
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
            // si c’est un dossier → récursion
            Pathfinder(file_path_folder1,file_path_folder2);
        }
        else if (S_ISREG(st1.st_mode)) {
            // si c’est un fichier → affichage
            check_file(entry1->d_name,folder2);
        }
    }

    closedir(dirf1);
    closedir(dirf2);
}

//-----------------------------------------------------------------

int main() {
    char *folder1 = "/home/juan/Bureau/BH_FolderMethod_test/test_orignal";
    char *folder2 = "/home/juan/Bureau/BH_FolderMethod_test/test_modified";

    Pathfinder(folder1, folder2);
    return 0;
}
