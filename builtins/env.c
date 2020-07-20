/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** env
*/

#include "builtins.h"
#include "my_puts.h"

void bi_env(command_t *com, stat_t *stat)
{
    char **raw_env = to_raw_env(stat->env);

    for (int i = 0; raw_env[i]; i++) {
        my_putstr(raw_env[i]);
        my_putstr("\n");
    }
    free_raw_env(raw_env);
}
