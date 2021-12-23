
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
#include <string.h>

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

void listdir(const char *dir_name)
{
    int fd;
    long nread;
    char *buf = (char *)malloc(BUF_SIZE);
    struct linux_dirent *d;
    char d_type;

    fd = open(dir_name, O_RDONLY | O_DIRECTORY);
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

            if (d_type == DT_REG ||
                (d_type == DT_DIR && d->d_name[0] != '.'))
            {
                printf("%c ", d_type == DT_REG ? 'f' : 'd');

#ifdef FILE_SIZE
                struct stat sb;
                int fstatat_flags = 0;
                int stat_res = fstatat(fd, d->d_name, &sb, fstatat_flags);
                if (stat_res == -1)
                    handle_error("fstatat");

                off_t st_size = sb.st_size;
                printf("%ld ", st_size);
#endif

                printf("%s/%s", dir_name, d->d_name);
                if (d_type == DT_DIR)
                    printf("/");
                printf("\n");

                int n = strlen(dir_name) + 1 + strlen(d->d_name);
                char *subdir_name = (char *)malloc(n);
                strcpy(subdir_name, dir_name);
                subdir_name[strlen(dir_name)] = '/'; /* overwrite the null terminater */
                strcpy(subdir_name + strlen(dir_name) + 1, d->d_name);

                if (d->d_name[0] != '.' // exclude "." and ".."
                    && d_type == DT_DIR)
                {
                    listdir(subdir_name);
                }
                free(subdir_name);
            }

            bpos += d->d_reclen;
        }
    }

    free(buf);
}

int main(int argc, char *argv[])
{
    char *dir_name = argc > 1 ? argv[1] : ".";
    listdir(dir_name);

    exit(EXIT_SUCCESS);
}
