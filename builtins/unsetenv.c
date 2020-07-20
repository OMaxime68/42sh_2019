/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** unsetenv
*/

#include "builtins.h"
#include "my_puts.h"
#include "string_utils.h"
#include <stdlib.h>

static int check_single(env_node_t **prev, env_node_t **it, char *tr, stat_t *s)
{
    if (my_streq((*it)->name, tr)) {
        if (*prev != NULL)
            (*prev)->next = (*it)->next;
        else
            s->env->first = NULL;
        s->env->count--;
        free((*it)->name);
        free((*it)->value);
        free((*it));
        return (1);
    }
    *prev = *it;
    *it = (*it)->next;
    return (0);
}

void bi_unsetenv(command_t *com, stat_t* stat)
{
    env_node_t *it = stat->env->first;
    env_node_t *prev = NULL;

    if (com->av[1] == NULL) {
        my_puterr("unsetenv: Too few arguments.\n");
        return;
    }
    while (it != NULL)
        if (check_single(&prev, &it, com->av[1], stat))
            return;
}
