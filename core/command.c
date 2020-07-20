/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** command
*/

#include "command.h"
#include "builtins.h"
#include "string_utils.h"
#include <stdlib.h>

static void *get_command_function(char **av)
{
    char *triggers[] = {"exit", "cd", "env", "setenv", "unsetenv"};
    void *functions[] = {bi_exit, bi_cd, bi_env, bi_setenv, bi_unsetenv};
    void *execute = bi_execute;

    for (int i = 0; i < 5; i++)
        if (my_streq(av[0], triggers[i]) > 0)
            return (functions[i]);
    return (execute);
}

char *get_command_at(char **commands, int i)
{
    if (i < 0)
        return (NULL);
    for (int j = 0; commands[j]; j++)
        if (j == i)
            return (commands[j]);
    return (NULL);
}

static int should_ignore(char **commands, int i)
{
    char *ignored[] = {"<", "<<", ">", ">>", NULL};
    char *previous = get_command_at(commands, i - 1);

    if (previous == NULL)
        return (0);
    for (int i = 0; ignored[i]; i++)
        if (my_streq(previous, ignored[i]))
            return (1);
    return (0);
}

void run_command(char **commands, int i, stat_t *stat)
{
    command_t command;
    void (*func)(command_t *, stat_t *);

    if (should_ignore(commands, i))
        return;
    build_command(&command, commands, i);
    func = get_command_function(command.av);
    func(&command, stat);
    free_raw_env(command.av);
}
