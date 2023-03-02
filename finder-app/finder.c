#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

void enumerateFiles( const char* dir, const char* search, int* numFiles, int* numFilesMatching);
int is_regular_file(const char *path);
int is_dir(const char *path);

int main(int argc, char** argv) {
    openlog(argv[0], 0, LOG_USER);

    if (argc < 3) {
        syslog(LOG_ERR, "Usage: writer FILESDIR SEARCHSTR\n");
        exit(1);
    }

    const char* FILESDIR = argv[1];
    const char* SEARCHSTR = argv[2];

    printf("FILESDIR=%s\n", FILESDIR);
    printf("SEARCHSTR=%s\n", SEARCHSTR);

    int numFiles = 0;
    int numFilesMatching = 0;
    enumerateFiles(FILESDIR, SEARCHSTR, &numFiles, &numFilesMatching);
}


void enumerateFiles( const char* path, const char* search, int* numFiles, int* numFilesMatching) {
    DIR* dir;
    FILE* handle;
    struct dirent *ent;
    if (is_dir(path)) {
        if ((dir = opendir (path)) != NULL) {
            while ((ent = readdir (dir)) != NULL) {
                (*numFiles)++;
                enumerateFiles(ent->d_name, search, numFiles, numFilesMatching);
            }
            closedir (dir); 
        }
    } else {
        handle = fopen(path, "r");
        if (handle == NULL) {
            syslog(LOG_ERR, "Iterated to a file we could not open: [%s]", path);
            return;
        }
        char buffer[256];
        while (fgets(buffer, 256, handle)) {
            if (strstr(buffer, search) != NULL) { 
                (numFilesMatching)++;
                fclose(handle);
                return;
            }
        }
        fclose(handle);
    }
}

int is_regular_file(const char *path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISREG(path_stat.st_mode);
}

int is_dir(const char *path) {
  struct stat path_stat;
  stat(path, &path_stat);
  return S_ISDIR(path_stat.st_mode);
}

