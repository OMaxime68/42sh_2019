/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019eeeeeeeee
** File description:aze
** cdeeeeeee
*/

#include "builtins.h"
#include "command.h"
#include "string_utils.h"
#include "env.h"
#include "my_puts.h"
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

static void set_old_pwd(stat_t *stat)
{
    char *old = getcwd(NULL, 0);
    command_t command;
    char *model[] = {NULL, "OLDPWD", old, NULL};

    command.av = model;
    bi_setenv(&command, stat);
}

static void print_error(char *final)
{
    my_puterr(final);
    my_puterr(": ");
    my_puterr(strerror(errno));
    my_puterr(".\n");
}

void bi_cd(command_t *com, stat_t *stat)
{
    char *home = get_env_var(stat->env, "HOME");
    char *model[] = {home, NULL, NULL};
    char *final = my_strdup(com->av[1]);

    if (com->av[1] == NULL)
        final = my_strdup(home);
    else if (com->av[1][0] == '~') {
        model[1] = com->av[1] + 1;
        final = my_strcat(model);
    } else if (com->av[1][0] == '-') {
        final = get_env_var(stat->env, "OLDPWD");
    }
    if (final == NULL)
        return;
    set_old_pwd(stat);
    if (chdir(final) < 0)
        print_error(final);
    free(home);
    free(final);
}
