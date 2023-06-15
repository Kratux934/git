#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <zip.h>
#include "decrypt_zip.h"

void decrypt_zip(const char *zipFilePath, const char *password) {
    struct zip *zipFile = zip_open(zipFilePath, 0, 'r');
    if (zipFile == NULL) {
        printf("Failed to open the zip file.\n");
        return;
    }

    int numEntries = zip_get_num_entries(zipFile, 0);
    if (numEntries < 0) {
        printf("Failed to get the number of entries in the zip file.\n");
        zip_close(zipFile);
        return;
    }

    int passwordCorrect = 0;
    const char *entryName;

    for (int i = 0; i < numEntries; i++) {
        entryName = zip_get_name(zipFile, i, 0);
        if (entryName == NULL) {
            printf("Failed to get the name of entry at index %d.\n", i);
            continue;
        }

        int result = zip_file_decrypt(zipFile, i, password);
        if (result == 0) {
            // Password matched, print the entry name
            printf("Entry: %s\n", entryName);
            passwordCorrect = 1;
        }
    }

    zip_close(zipFile);

    if (!passwordCorrect) {
        printf("Failed to open the zip file or password not found.\n");
    }
}
