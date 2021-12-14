
/*
This code was inspired by the following articles:
- https://gigazine.net/news/20210818-million-files-long-time-ls/
- http://be-n.com/spw/you-can-list-a-million-files-in-a-directory-but-not-with-ls.html

*/

#define _GNU_SOURCE
#include <dirent.h> /* Defines DT_* constants */
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/syscall.h>

#define handle_error(msg)   \
    do                      \
    {                       \
        perror(msg);        \
        exit(EXIT_FAILURE); \
    } while (0)

struct linux_dirent
{
    unsigned long d_ino;
    off_t d_off;
    unsigned short d_reclen;
    char d_name[];
};

#define BUF_SIZE 1024 * 1024 * 5

int main(int argc, char *argv[])
{
    int fd;
    long nread;
    char buf[BUF_SIZE];
    struct linux_dirent *d;
    char d_type;

    fd = open(argc > 1 ? argv[1] : ".", O_RDONLY | O_DIRECTORY);
    if (fd == -1)
        handle_error("open");

    for (;;)
    {
        nread = syscall(SYS_getdents, fd, buf, BUF_SIZE);
        if (nread == -1)
            handle_error("getdents");

        if (nread == 0)
            break;

        for (long bpos = 0; bpos < nread;)
        {
            d = (struct linux_dirent *)(buf + bpos);
            d_type = *(buf + bpos + d->d_reclen - 1);

            if (d_type == DT_REG || d_type == DT_DIR)
            {
                struct stat sb;
                int fstatat_flags = 0;
                int stat_res = fstatat(fd, d->d_name, &sb, fstatat_flags);
                off_t st_size = sb.st_size;

                printf("%d ", st_size);

                printf("%s", d->d_name);
                if (d_type == DT_DIR)
                    printf("/");

                printf("\n");
            }

            bpos += d->d_reclen;
        }
    }

    exit(EXIT_SUCCESS);
}
