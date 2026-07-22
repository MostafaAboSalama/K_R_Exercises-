#include <stdio.h>
#include <stdlib.h>

#define LINES_PER_PAGE 50

void filecopy(FILE *ifp, FILE *ofp, const char *filename);
void print_header(FILE *ofp, const char *filename, int page);

int main(int argc, char *argv[])
{
    FILE *fp;

    if (argc == 1)
    {
        fprintf(stderr, "missing file name\n");
        exit(1);
    }

    while (--argc > 0)
    {
        if ((fp = fopen(*++argv, "r")) == NULL)
        {
            fprintf(stderr, "can't open %s\n", *argv);
            continue;               /* Try remaining files */
        }

        filecopy(fp, stdout, *argv);
        fclose(fp);
    }

    if (ferror(stdout))
    {
        fprintf(stderr, "error writing to stdout\n");
        exit(2);
    }

    return 0;
}

void filecopy(FILE *ifp, FILE *ofp, const char *filename)
{
    int c;
    int line_cnt = 0;
    int page_cnt = 1;

    print_header(ofp, filename, page_cnt);

    while ((c = getc(ifp)) != EOF)
    {
        putc(c, ofp);

        if (c == '\n')
        {
            line_cnt++;

            if (line_cnt == LINES_PER_PAGE)
            {
                page_cnt++;
                line_cnt = 0;

                /* Print header for the next page */
                print_header(ofp, filename, page_cnt);
            }
        }
    }
}

void print_header(FILE *ofp, const char *filename, int page)
{
    fprintf(ofp, "=====================================\n");
    fprintf(ofp, "File: %s\n", filename);
    fprintf(ofp, "Page: %d\n", page);
    fprintf(ofp, "=====================================\n");
}
