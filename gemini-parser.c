#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) {
	    fprintf(stderr, "Usage: %s <file.gmi>\n", argv[0]);
	    return 1;
    }

    FILE *file = fopen(argv[1], "r");

    // 512 bytes buffer to store each line
    char line[512];

    int in_code_block = 0;

    if (file != NULL)
    {
        while (fgets(line, sizeof(line), file)) {
            
            if(in_code_block == 1 && strncmp(line, "```", 3) != 0) {
                printf("in code block: %s", line);
            }

            if(strncmp(line, "# ", 2) == 0) {
                printf("# detected:\t %s", line);
            }
            else if(strncmp(line, "## ", 3) == 0) {
                printf("## detected:\t %s", line);
            }
            else if(strncmp(line, "### ", 4) == 0) {
                printf("### detected:\t %s", line);
            }
            else if(strncmp(line, "=>", 2) == 0) {
                printf("=> detected:\t %s", line);
            }
            else if(strncmp(line, "*", 1) == 0) {
                printf("* detected:\t %s", line);
            }
            else if(strncmp(line, ">", 1) == 0) {
                printf("> detected:\t %s", line);
            }
            else if(strncmp(line, "```", 3) == 0) {
                if(in_code_block == 0) {
                    in_code_block = 1;
                    printf("``` start detected:\t %s", line);
                }
                else {
                    in_code_block = 0;
                    printf("``` end detected:\t %s", line);
                }
            }
	    }
	    fclose(file);
    }
    else {
	    fprintf(stderr, "Unable to open file!\n");
	    return 1;
    }

    return 0;
}
