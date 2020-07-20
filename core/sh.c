/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** sh
*/

#include "sh.h"
#include "env.h"
#include "input_to_commands.h"
#include "my_puts.h"
#include "string_utils.h"
#include "command.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int sh_exit(stat_t *stat)
{
    if (isatty(0))
        my_putstr("exit\n");
    stat->should_quit = 0;
    return (0);
}

static int free_ret(void *ptr)
{
    free(ptr);
    return (0);
}

int sh_step(stat_t *stat)
{
    char *input = NULL;
    char **splits;
    size_t len;

    my_putstr(isatty(0) ? PROMPT : "");
    if (getline(&input, &len, stdin) == -1)
        return (sh_exit(stat));
    if (my_strlen(input) <= 1)
        return (free_ret(input));
    if (input[my_strlen(input) - 1] == '\n')
        input[my_strlen(input) - 1] = 0;
    splits = input_to_commands(input);
    for (int i = 0; splits[i]; i++) {
        if (!starts_with_splitter(splits[i]))
            run_command(splits, i, stat);
    }
    free_raw_env(splits);
    return (free_ret(input));
}
