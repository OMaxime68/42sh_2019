/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** main
*/

#include "stat.h"
#include "sh.h"
#include <stddef.h>

int main(int ac, char **av, char **raw_env)
{
    stat_t *stat = init_stat(raw_env);
    int result;

    if (stat == NULL)
        return (84);
    while (stat->should_quit < 0)
        sh_step(stat);
    result = stat->should_quit;
    free_stat(stat);
    return (result);
}