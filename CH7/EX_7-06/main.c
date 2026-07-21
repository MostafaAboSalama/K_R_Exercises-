#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINE 100

int main(int argc, char *argv[])
{
    FILE *fp1, *fp2;
    char file1_line[MAXLINE];
    char file2_line[MAXLINE];
    char *line1;
    char *line2;

    int identical = 1;
    int different_width = 0;

    char *prog = argv[0];

    if (argc != 3)
        fprintf(stderr, "%s: must enter 2 files\n", prog);
    else
    {
        if ((fp1 = fopen(*++argv, "r")) == NULL ||
            (fp2 = fopen(*++argv, "r")) == NULL)
        {
            fprintf(stderr, "%s: can't open files\n", prog);
            exit(1);
        }
        else
        {
            for (;;)
            {
                /* Read one line from each file */
                line1 = fgets(file1_line, MAXLINE, fp1);
                line2 = fgets(file2_line, MAXLINE, fp2);

                /* Both files reached EOF together */
                if (line1 == NULL && line2 == NULL)
                {
                    identical = 1;
                    break;
                }

                /* One file ended before the other */
                else if ((line1 != NULL && line2 == NULL) ||
                         (line1 == NULL && line2 != NULL))
                {
                    identical = 0;
                    different_width = 1;
                    break;
                }

                /* First differing line */
                else if (strcmp(line1, line2) != 0)
                {
                    identical = 0;
                    break;
                }
            }
        }
    }

    if (identical)
        printf("Identical\n");
    else
    {
        printf("Not Identical\n");

        if (different_width)
            printf("The two files have different lengths.\n");
        else
        {
            printf("The first line where they differ:\n");
            printf("file1: %s", file1_line);
            printf("file2: %s", file2_line);
        }
    }

    if (ferror(stdout))
    {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }

    fclose(fp1);
    fclose(fp2);

    return 0;
}
