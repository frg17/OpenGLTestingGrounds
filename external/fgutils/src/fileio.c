#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "errno.h"

#include "fgutils/logs.h"
#include "fgutils/fileio.h"

/**
 * @parameter char *fileName: Name of file to read.
 * @return char*: String with contents of file.
 */
const char *fgReadFile(const char *fileName) {
    int rc = 0;
    int fLength = 0;
    char* contents;

    FILE *f = fopen(fileName, "r");
    if(!f) goto error;

    rc = fseek(f, 0, SEEK_END);
    if(rc) goto error;

    fLength = ftell(f);
    rc = fseek(f, 0, SEEK_SET);
    if(rc) goto error;

    contents = (char *) calloc(fLength + 1, sizeof(char));
    fread(contents, sizeof(char), fLength, f);
    fclose(f);
    
    return contents;

error:
    fgLog("%s", strerror(errno));
    exit(EXIT_FAILURE);
}