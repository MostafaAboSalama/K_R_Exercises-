#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef VERSION
#define VERSION 1     	/* Default implementation if -DVERSION isn't supplied */
#endif

/*
 * VERSION 1 : stdio (getc/putc)
 * VERSION 2 : POSIX read/write, one byte at a time
 * VERSION 3 : POSIX read/write with a 1024-byte buffer
 *
 * Compile examples:
 * gcc cat.c -DVERSION=1 -o cat_stdio
 * gcc cat.c -DVERSION=2 -o cat_byte
 * gcc cat.c -DVERSION=3 -o cat_buffer
 */


#if VERSION == 1

/* ---------- CH7 : stdio ---------- */

void filecopy(FILE *ifp, FILE *ofp);

int main(int argc, char *argv[])
{
    printf("VERSION = %d\n", VERSION);
    
    FILE *fp;

    if (argc == 1)
        filecopy(stdin, stdout);
    else {
        while (--argc > 0) {
            if ((fp = fopen(*++argv, "r")) == NULL) {
                fprintf(stderr, "can't open %s\n", *argv);
                exit(1);
            }

            filecopy(fp, stdout);
            fclose(fp);
        }
    }

    return 0;
}

void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

#elif VERSION == 2

/* ---------- CH8 : read/write one byte ---------- */

void filecopy(int ifd, int ofd);

int main(int argc, char *argv[])
{
    printf("VERSION = %d\n", VERSION);
    
    int fd;

    if (argc == 1)
        filecopy(STDIN_FILENO, STDOUT_FILENO);
    else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY)) < 0) {
                fprintf(stderr, "can't open %s\n", *argv);
                exit(1);
            }

            filecopy(fd, STDOUT_FILENO);
            close(fd);
        }
    }

    return 0;
}

/* Copy one byte per system call (intentionally inefficient). */
void filecopy(int ifd, int ofd)
{
    char c;

    while (read(ifd, &c, 1) > 0)
        write(ofd, &c, 1);
}

#elif VERSION == 3

/* ---------- CH8 : buffered read/write ---------- */

void filecopy(int ifd, int ofd);

int main(int argc, char *argv[])
{
    printf("VERSION = %d\n", VERSION);
    
    int fd;

    if (argc == 1)
        filecopy(STDIN_FILENO, STDOUT_FILENO);
    else {
        while (--argc > 0) {
            if ((fd = open(*++argv, O_RDONLY)) < 0) {
                fprintf(stderr, "can't open %s\n", *argv);
                exit(1);
            }

            filecopy(fd, STDOUT_FILENO);
            close(fd);
        }
    }

    return 0;
}

/* Copy blocks of data to reduce the number of system calls. */
void filecopy(int ifd, int ofd)
{
    char buf[1024];			/* Temporary buffer used by read()/write() */
    ssize_t n;				 /* read() returns the number of bytes read */

    while ((n = read(ifd, buf, sizeof(buf))) > 0)
        write(ofd, buf, n);
}

#else

#error "VERSION must be 1, 2, or 3"

#endif


/*
 * Performance experiment (100 KB file):
 *
 * Version    real      user      sys
 * --------------------------------------
 * stdio      0.002 s   0.001 s   0.001 s
 * 1-byte     0.124 s   0.039 s   0.085 s
 * buffered   0.002 s   0.000 s   0.002 s
 *
 * Observations:
 *
 * 1. The one-byte version is much slower because every byte requires
 *    one read() and one write() system call.
 *
 * 2. The buffered version performs nearly the same as stdio because
 *    both reduce the number of system calls by transferring many bytes
 *    at once.
 *
 * 3. The experiment shows that buffering—not the choice between
 *    getc()/putc() and read()/write()—is the primary reason for the
 *    performance difference.
 */
