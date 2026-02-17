#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>

const char* CSS = 
"<style>\n"
"body { \n"
"    background: #fafafa; \n"
"    color: #0a0a0a; \n"
"    font-family: 'Courier New', 'Courier', monospace;\n"
"    max-width: 780px; \n"
"    margin: 0 auto; \n"
"    padding: 4rem 2rem; \n"
"    line-height: 1.65; \n"
"    min-height: 100vh; \n"
"    border-left: 1px solid #e0e0e0; \n"
"    border-right: 1px solid #e0e0e0; \n"
"}\n"
"@media (max-width: 768px) {\n"
"    body {\n"
"        padding: 2rem 1rem;\n"
"        border-left: none;\n"
"        border-right: none;\n"
"    }\n"
"}\n"
"h1 { \n"
"    color: #0a0a0a; \n"
"    font-size: 2.5rem; \n"
"    font-weight: 700; \n"
"    letter-spacing: -0.02em; \n"
"    margin-bottom: 0.5rem; \n"
"    text-transform: uppercase; \n"
"    border-bottom: 2px solid #7c3aed; \n"
"    padding-bottom: 0.5rem; \n"
"    word-wrap: break-word;\n"
"}\n"
"@media (max-width: 768px) {\n"
"    h1 {\n"
"        font-size: 1.8rem;\n"
"    }\n"
"}\n"
"h2 { \n"
"    color: #171717; \n"
"    font-size: 1.5rem; \n"
"    font-weight: 700; \n"
"    margin-top: 3rem; \n"
"    margin-bottom: 1rem; \n"
"    text-transform: uppercase; \n"
"    letter-spacing: 0.05em; \n"
"    word-wrap: break-word;\n"
"}\n"
"@media (max-width: 768px) {\n"
"    h2 {\n"
"        font-size: 1.3rem;\n"
"        margin-top: 2rem;\n"
"    }\n"
"}\n"
"h3 { \n"
"    color: #404040; \n"
"    font-size: 1.1rem; \n"
"    font-weight: 700; \n"
"    margin-top: 2rem; \n"
"    margin-bottom: 0.75rem; \n"
"    letter-spacing: 0.03em; \n"
"    word-wrap: break-word;\n"
"}\n"
"@media (max-width: 768px) {\n"
"    h3 {\n"
"        font-size: 1rem;\n"
"    }\n"
"}\n"
"a { \n"
"    color: #7c3aed; \n"
"    text-decoration: none; \n"
"    font-weight: 700; \n"
"    border-bottom: 2px solid #7c3aed; \n"
"    transition: all 0.1s; \n"
"    word-wrap: break-word;\n"
"}\n"
"a:hover { \n"
"    color: #ffffff; \n"
"    background: #7c3aed; \n"
"    padding: 2px 6px; \n"
"    border-bottom: 2px solid #7c3aed; \n"
"}\n"
"pre { \n"
"    background: #1a1a1a; \n"
"    color: #e0e0e0; \n"
"    padding: 1.5rem; \n"
"    border-radius: 4px; \n"
"    overflow-x: auto; \n"
"    font-size: 0.9rem; \n"
"    line-height: 1.6; \n"
"    border: 1px solid #7c3aed; \n"
"    margin: 2rem 0; \n"
"    max-width: 100%;\n"
"}\n"
"@media (max-width: 768px) {\n"
"    pre {\n"
"        padding: 1rem;\n"
"        font-size: 0.8rem;\n"
"        margin: 1.5rem 0;\n"
"    }\n"
"}\n"
"code { \n"
"    color: #7c3aed; \n"
"    font-weight: 700; \n"
"    background: #f0f0f0; \n"
"    padding: 2px 6px; \n"
"    border-radius: 2px; \n"
"    word-wrap: break-word;\n"
"}\n"
"pre code { \n"
"    color: #e0e0e0; \n"
"    background: transparent; \n"
"    padding: 0; \n"
"}\n"
"blockquote { \n"
"    border-left: 4px solid #7c3aed; \n"
"    padding-left: 1.5rem; \n"
"    color: #525252; \n"
"    font-style: italic; \n"
"    margin: 2rem 0; \n"
"    background: #f5f5f5; \n"
"    padding: 1rem 1.5rem; \n"
"}\n"
"@media (max-width: 768px) {\n"
"    blockquote {\n"
"        padding-left: 1rem;\n"
"        padding: 0.75rem 1rem;\n"
"        margin: 1.5rem 0;\n"
"    }\n"
"}\n"
"ul { \n"
"    padding-left: 2rem; \n"
"    margin: 1.5rem 0; \n"
"}\n"
"@media (max-width: 768px) {\n"
"    ul {\n"
"        padding-left: 1.5rem;\n"
"    }\n"
"}\n"
"li { \n"
"    margin-bottom: 0.6rem; \n"
"    color: #171717; \n"
"}\n"
"li::marker { \n"
"    content: '> '; \n"
"    color: #7c3aed; \n"
"    font-weight: 700; \n"
"}\n"
"p { \n"
"    margin: 1.25rem 0; \n"
"    color: #171717; \n"
"    word-wrap: break-word;\n"
"}\n"
".logo { \n"
"    display: block; \n"
"    max-width: 150px; \n"
"    margin: 0 auto 2rem auto; \n"
"}\n"
"</style>\n";

void write_html_header(FILE *output, const char *title) {
    fprintf(output, "<!DOCTYPE html>\n");
    fprintf(output, "<html>\n");
    fprintf(output, "<head>\n");
    fprintf(output, "<meta charset=\"utf-8\">\n");
    fprintf(output, "<title>%s</title>\n", title);
    fprintf(output, "<link rel=\"icon\" type=\"image/png\" href=\"/Logo.png\">\n");
    fprintf(output, "%s", CSS);
    fprintf(output, "</head>\n");
    fprintf(output, "<body>\n");
    fprintf(output, "<img src=\"/Logo.png\" alt=\"guifl.com\" class=\"logo\">\n");
}

void parse_gemtext_to_html(const char *gemtext_dir, const char *html_dir, char *name) {
    char html_path[512];
    char gemtext_path[512];

    snprintf(html_path, sizeof(html_path), "%s/%s.html", html_dir, name);
    snprintf(gemtext_path, sizeof(gemtext_path), "%s/%s.gmi", gemtext_dir, name);

    FILE *html_file = fopen(html_path, "w");

    write_html_header(html_file, "guifl.com Gemini Capsule");

    FILE *file = fopen(gemtext_path, "r");

    // 512 bytes buffer to store each line
    char line[512];

    int in_code_block = 0;
    int in_list = 0;

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
            else if(strncmp(line, "* ", 2) == 0) {
                if(in_list == 0) {
                    in_list = 1;
                    fprintf(html_file, "<ul>\n");
                }
                printf("LIST:\t %s", line+2);
                
                fprintf(html_file, "<li>%s</li>\n", line+1);
            }
            else if(strncmp(line, ">", 1) == 0) {
                printf("QUOTE:\t %s", line+1);
                fprintf(html_file, "<blockquote>%s</blockquote>\n", line+1);
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
            else if(in_list == 1 && strncmp(line, "* ", 2) != 0) {
                in_list = 0;
                fprintf(html_file, "</ul>\n");
            }
            else {
                if(strncmp(line, "", 1) == 0 || strncmp(line, " ", 1) == 0) {
                    continue;
                }

                if(in_list == 1) {
                    in_list = 0;
                    fprintf(html_file, "</ul>\n");
                }

                printf("TEXT:\t %s", line);
                fprintf(html_file, "<p>%s</p>\n", line);
            }
	    }
	    fclose(file);
    }
    else {
	    fprintf(stderr, "Unable to open file!\n");
    }

    fprintf(html_file, "</body>\n</html>");
    fclose(html_file);
}

void process_directory(const char *gemtext_dir, const char *html_dir) {
    mkdir(html_dir, 0755);

    struct dirent *de;
    DIR *dr = opendir(gemtext_dir);

    if(dr == NULL) {
        fprintf(stderr, "Cannot open directory: %s\n", gemtext_dir);
        return;
    }

    char** strings = (char**)malloc(100*sizeof(char*));
    if (strings == NULL) {
        closedir(dr);
        return;
    }

    int count = 0;
    while((de = readdir(dr)) != NULL) {
        if(strncmp(de->d_name, ".", 1) != 0 && strstr(de->d_name, ".gmi") != NULL) {
            strings[count] = (char*)malloc(256);
            sprintf(strings[count], "%s", de->d_name);
            count++;
        }
    }
    closedir(dr);

    for(int i = 0; i < count; i++) {
        char *dot = strchr(strings[i], '.');
        if(dot) *dot = '\0';
        parse_gemtext_to_html(gemtext_dir, html_dir, strings[i]);
        free(strings[i]);
    }

    free(strings);
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;

    process_directory("./gemtext", "./html");
    process_directory("./gemtext/fr", "./html/fr");
    process_directory("./gemtext/blog", "./html/blog");

    return 0;
}
