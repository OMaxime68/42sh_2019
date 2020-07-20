/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** fs
*/

#include "fs.h"
#include <sys/types.h>
#include <sys/stat.h>

int fs_entry_exists(char *path)
{
    struct stat sb;

    return (stat(path, &sb) == 0);
}

int fs_is_executable(char *path)
{
    struct stat sb;

    if (stat(path, &sb) < 0)
        return (0);
    if ((sb.st_mode & __S_IFMT) == __S_IFDIR)
        return (0);
    return (sb.st_mode & S_IXUSR);
}
