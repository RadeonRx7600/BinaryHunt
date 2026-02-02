#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/sha.h>
#include <sys/stat.h>

/*
void SHA256sum_files(const char *file_name) {
    //FUNCTION ___STATUS(OK)___

    FILE *f = fopen(file_name, "rb");
    if (!f) {
        printf("error : cannot acces folder ...");
        return 1;
    }

    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    unsigned char buffer[1024];
    size_t lu;
    while ((lu = fread(buffer, 1, sizeof(buffer), f)) > 0) {
        SHA256_Update(&ctx, buffer, lu);
    }

    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &ctx);

    fclose(f);

    //printf("SHA256(%s) = ", file_name);
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
        printf("%02x", hash[i]);
    printf("\n");
}
*/

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