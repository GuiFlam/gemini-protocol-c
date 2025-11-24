#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const char* CSS = 
"<style>\n"
"body { \n"
"    background-color: #ffffff; \n"
"    color: #333333; \n"
"    font-family: -apple-system, BlinkMacSystemFont, 'Segoe UI', Roboto;\n"
"    max-width: 800px; \n"
"    margin: 0 auto; \n"
"    padding: 2rem 1rem; \n"
"    line-height: 1.65; \n"
"}\n"
"h1 { color: #111; font-size: 2.5rem; font-weight: 700; }\n"
"h2 { color: #222; font-size: 1.75rem; font-weight: 650; }\n"
"h3 { color: #333; font-size: 1.25rem; }\n"
"a { color: #0056b3; text-decoration: none; border-bottom: 1px dotted #0056b3; }\n"
"pre { background: #f8f9fa; padding: 1.2rem; border: 1px solid #e9ecef; border-radius: 4px; }\n"
"blockquote { border-left: 3px solid #333; padding-left: 1.2rem; color: #666; font-style: italic; }\n"
"li { margin-bottom: 0.4rem; }\n"
"</style>\n";

void write_html_header(FILE *output, const char *title) {
    fprintf(output, "<!DOCTYPE html>\n");
    fprintf(output, "<html>\n");
    fprintf(output, "<head>\n");
    fprintf(output, "<meta charset=\"utf-8\">\n");
    fprintf(output, "<title>%s</title>\n", title);
    fprintf(output, "%s", CSS);
    fprintf(output, "</head>\n");
    fprintf(output, "<body>\n");
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
	    fprintf(stderr, "Usage: %s <file.gmi>\n", argv[0]);
	    return 1;
    }
 
    FILE *html_file = fopen("index.html", "w");

    write_html_header(html_file, "guifl.com Gemini Capsule");

    FILE *file = fopen(argv[1], "r");

    // 512 bytes buffer to store each line
    char line[512];

    int in_code_block = 0;

    if (file != NULL)
    {
        while (fgets(line, sizeof(line), file)) {

            line[strcspn(line, "\n")] = '\0';

            if(in_code_block == 1 && strncmp(line, "```", 3) != 0) {
                printf("in code block: %s", line);
                fprintf(html_file, "%s\n", line);
                continue;
            }

            if(strncmp(line, "# ", 2) == 0) {
                printf("H1:\t %s", line+2);
                fprintf(html_file, "<h1>%s</h1>\n", line+2);
            }
            else if(strncmp(line, "## ", 3) == 0) {
                printf("H2:\t %s", line+3);
                fprintf(html_file, "<h2>%s</h2>\n", line+3);
            }
            else if(strncmp(line, "### ", 4) == 0) {
                printf("H3:\t %s", line+4);
                fprintf(html_file, "<h3>%s</h3>\n", line+4);
            }
            else if(strncmp(line, "=>", 2) == 0) {

                char *url_pos = line + 3;
                char *space_pos = strchr(url_pos, ' ');

                if(space_pos != NULL) {
                    char url[512];
                    int url_len = space_pos - url_pos;
                    strncpy(url, url_pos, url_len);
                    url[url_len] = '\0';
                    printf("LINK:\t %s, NAME: %s", url, space_pos+1);
                    fprintf(html_file, "<a href=\"%s\">%s</a><br>\n", url, space_pos+1);
                }
                else {
                    printf("LINK:\t %s", url_pos);
                    fprintf(html_file, "<a href=\"%s\">%s</a><br>\n", url_pos, url_pos);
                }
            }
            else if(strncmp(line, "*", 1) == 0) {
                printf("LIST:\t %s", line+1);
                fprintf(html_file, "<ul>%s</ul>\n", line+1);
            }
            else if(strncmp(line, ">", 1) == 0) {
                printf("QUOTE:\t %s", line+1);
                fprintf(html_file, "<blockquote>%s</blockquote><br>\n", line+1);
            }
            else if(strncmp(line, "```", 3) == 0) {
                if(in_code_block == 0) {
                    in_code_block = 1;
                    printf("CODE BLOCK START:\t %s", line);
                    fprintf(html_file, "<pre><code>");
                }
                else {
                    in_code_block = 0;
                    printf("CODE BLOCK END:\t %s", line);
                    fprintf(html_file, "</code></pre>\n");
                }
            }
            else if(strncmp(line, "\n", 1) == 0) {
                printf("EMPTY LINE\n");
                fprintf(html_file, "<br>\n");
            }
            else {
                printf("TEXT:\t %s", line);
                fprintf(html_file, "<p>%s</p>", line);
            }
	    }
	    fclose(file);
    }
    else {
	    fprintf(stderr, "Unable to open file!\n");
	    return 1;
    }

    fprintf(html_file, "</body>\n</html>");
    fclose(html_file);

    return 0;
}
