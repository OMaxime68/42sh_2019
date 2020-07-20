/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** setenv
*/

#include "builtins.h"
#include "string_utils.h"
#include "my_puts.h"
#include <stdlib.h>

static int try_replace(char **av, stat_t *stat)
{
    env_node_t *it = stat->env->first;

    while (it != NULL) {
        if (my_streq(av[1], it->name) > 0) {
            it->value = my_strdup(av[2] != NULL ? av[2] : "");
            return (1);
        }
        it = it->next;
    }
    return (0);
}

static void new(char **av, stat_t *stat)
{
    env_node_t *it = stat->env->first;
    env_node_t *new = malloc(sizeof(env_node_t *));

    new->name = my_strdup(av[1]);
    new->value = my_strdup(av[2] != NULL ? av[2] : "");
    new->next = NULL;
    stat->env->count++;
    it = stat->env->first;
    if (it != NULL) {
        while (it->next != NULL)
            it = it->next;
        it->next = new;
    } else
        stat->env->first = new;
}

static int is_alphanumeric(char const *str)
{
    for (int i = 0; str[i]; i++) {
        if (!((str[i] >= 'a' && str[i] <= 'z') ||
        (str[i] >= 'A' && str[i] <= 'Z') ||
        (str[i] >= '0' && str[i] <= '9')))
            return (0);
    }
    return (1);
}

void bi_setenv(command_t *com, stat_t *stat)
{
    if (com->av[1] == NULL) {
        bi_env(com, stat);
        return;
    }
    if (!is_alphanumeric(com->av[1])) {
        my_puterr("setenv:"
        " Variable name must contain alphanumeric characters.\n");
        return;
    }
    if (try_replace(com->av, stat))
        return;
    new(com->av, stat);
}
