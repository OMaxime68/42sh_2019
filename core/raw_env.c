/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** raw_env
*/

#include "env.h"
#include "string_utils.h"
#include <stdlib.h>

char **to_raw_env(env_t const *env)
{
    char **res = malloc(sizeof(char *) * (env->count + 1));
    char *model[] = {NULL, "=", NULL, NULL};
    env_node_t *it = env->first;
    int res_i = 0;

    while (it != NULL) {
        model[0] = it->name;
        model[2] = it->value;
        res[res_i++] = my_strcat(model);
        it = it->next;
    }
    res[res_i] = NULL;
    return (res);
}

void free_raw_env(char **raw_env)
{
    for (int i = 0; raw_env[i]; i++)
        free(raw_env[i]);
    free(raw_env);
}