/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** command_error
*/

#include "command.h"
#include "my_puts.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void print_command_error(int status)
{
    if (WIFSIGNALED(status) != 0) {
        if (WTERMSIG(status) == 8 && WCOREDUMP(status) == 0)
            my_puterr("Floating exception\n");
        else if (WTERMSIG(status) != 8 && WCOREDUMP(status) != 0)
            my_puterr("Floating exception (core dumped)\n");
        if (WTERMSIG(status) == 11 && WCOREDUMP(status) == 0)
            my_puterr("Segmentation fault\n");
        else if (WTERMSIG(status) != 11 && WCOREDUMP(status) != 0)
            my_puterr("Segmentation fault (core dumped)\n");
    }
    if (WIFSTOPPED(status) != 0)
        if (WSTOPSIG(status) != 0)
            my_puterr(strsignal(WSTOPSIG(status)));
}
