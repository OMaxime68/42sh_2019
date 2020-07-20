/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** execute
*/

#include "builtins.h"
#include "command.h"
#include "string_utils.h"
#include "my_puts.h"
#include "fs.h"
#include "path.h"
#include <stdlib.h>

static int is_local(char *path)
{
    if (path[0] == '.' && path[1] == '/')
        return (1);
    if (path[0] == '.' && path[1] == '.' && path[2] == '/')
        return (1);
    if (path[0] == '/')
        return (1);
    return (0);
}

static char *resolve_path(char *path, stat_t *stat)
{
    if (is_local(path))
        return (my_strdup(path));
    return (search_in_path(path, stat->env));
}

static void replace_home(char **av, stat_t *stat)
{
    char *home = get_env_var(stat->env, "HOME");
    char *model[] = {home, "/", NULL, NULL};
    char *temp;

    for (int i = 0; av[i]; i++)
        if (av[i][0] == '~') {
            model[2] = av[i] + 1;
            temp = my_strcat(model);
            free(av[i]);
            av[i] = temp;
        }
    free(home);
}

void bi_execute(command_t *com, stat_t *stat)
{
    replace_home(com->av, stat);
    com->exec = resolve_path(com->av[0], stat);
    if (com->exec == NULL) {
        my_puterr2(com->av[0], ": Command not found.\n");
        return;
    }
    if (fs_entry_exists(com->exec) == 0) {
        my_puterr2(com->av[0], ": Command not found.\n");
        free(com->exec);
        return;
    }
    if (fs_is_executable(com->exec) == 0) {
        my_puterr2(com->av[0], ": Permission denied.\n");
        free(com->exec);
        return;
    }
    exec_command(com, stat);
    free(com->exec);
}
