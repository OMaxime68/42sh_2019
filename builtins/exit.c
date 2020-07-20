/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** exit
*/

#include "builtins.h"
#include "my_puts.h"
#include "string_convert.h"
#include <stddef.h>

void bi_exit(command_t *com, stat_t *stat)
{
    my_putstr("exit\n");
    if (com->av[1] != NULL) {
        stat->should_quit = stoi(com->av[1]) % 256;
        if (stat->should_quit < 0)
            stat->should_quit = 256 + stat->should_quit;
        return;
    }
    stat->should_quit = 0;
}
