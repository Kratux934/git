#include <stdio.h>
#include <zip.h>
#include "open_zip.h"

void open_zip(const char *zipFilePath) {
    struct zip *za = zip_open(zipFilePath, 0, NULL);
    if (za == NULL) {
        printf("Failed to open the zip file.\n");
        return;
    }

    int numEntries = zip_get_num_entries(za, 0);
    for (int i = 0; i < numEntries; i++) {
        struct zip_stat st;
        zip_stat_init(&st);
        if (zip_stat_index(za, i, 0, &st) == 0) {
            const char *entryName = st.name;
            printf("Entry: %s\n", entryName);
        }
    }

    zip_close(za);
}
