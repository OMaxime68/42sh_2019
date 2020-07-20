/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** stat
*/

#include "stat.h"
#include "env.h"
#include <stdlib.h>

stat_t *init_stat(char **raw_env)
{
    stat_t* stat = malloc(sizeof(stat_t));

    if (stat == NULL)
        return (NULL);
    stat->env = parse_env(raw_env);
    if (stat->env == NULL) {
        free(stat);
        return (NULL);
    }
    stat->should_quit = -1;
    stat->pipe = -1;
    stat->pid_to_wait[0] = -1;
    return (stat);
}

void free_stat(stat_t *stat)
{
    free_env(stat->env);
    free(stat);
}
