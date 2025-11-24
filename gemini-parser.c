#include <stdio.h>
#include <stdlib.h>

// TODO: Detect all the .gmi syntax

int main(int argc, char *argv[])
{
    if (argc != 2) {
	    fprintf(stderr, "Usage: %s <file.gmi>\n", argv[0]);
	    return 1;
    }

    FILE *file = fopen(argv[1], "r");

    // 512 bytes buffer to store each line
    char line[512];

    if (file != NULL)
    {
        while (fgets(line, sizeof(line), file)) {
            printf("%s", line);
	    }
	    fclose(file);
    }
    else {
	    fprintf(stderr, "Unable to open file!\n");
	    return 1;
    }

    return 0;
}
