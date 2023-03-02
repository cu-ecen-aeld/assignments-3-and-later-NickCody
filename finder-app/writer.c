#include <stdio.h>
#include <syslog.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>

int main(int argc, char** argv) {
    openlog(argv[0], 0, LOG_USER);

    if (argc < 3) {
        syslog(LOG_ERR, "Usage: writer WRITEFILE WRITESTR\n");
        exit(1);
    }

    const char* WRITEFILE = argv[1];
    const char* WRITESTR = argv[2];

    FILE* handle = fopen(WRITEFILE, "w+");
    if (handle == NULL) {
        syslog(LOG_ERR, "Could not open file [%s]", WRITEFILE);
        exit(1);
    }
    syslog(LOG_DEBUG, "Writing %s to %s", WRITESTR, WRITEFILE);
    fprintf(handle, "%s", WRITESTR);    
    fclose(handle);
}
