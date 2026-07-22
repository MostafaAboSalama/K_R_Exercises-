#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LEN 100

void search_file(FILE *fp, char *pattern);

int main(int argc, char *argv[])
{
    FILE *fp;
    char *pattern;

    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s pattern [file ...]\n", argv[0]);
        exit(1);
    }

    pattern = argv[1];

    /* No files: search standard input */
    if (argc == 2)
    {
        search_file(stdin, pattern);
    }
    else
    {
        /* Search each file */
        for (int i = 2; i < argc; i++)
        {
            if ((fp = fopen(argv[i], "r")) == NULL)
            {
                fprintf(stderr, "can't open %s\n", argv[i]);
                continue;
            }

            search_file(fp, pattern);
            fclose(fp);
        }
    }

    if (ferror(stdout))
    {
        fprintf(stderr, "error writing to stdout\n");
        exit(2);
    }

    return 0;
}

void search_file(FILE *fp, char *pattern)
{
    char line[MAX_LEN];

    while (fgets(line, MAX_LEN, fp) != NULL)
    {
        if (strstr(line, pattern))
            printf("%s", line);     
    }
}
