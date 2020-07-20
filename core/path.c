/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** path
*/

#include "path.h"
#include "env.h"
#include "fs.h"
#include "string_utils.h"
#include <stdlib.h>

static int count_paths(char *path_env_var)
{
    int count = 1;

    if (path_env_var == NULL)
        return (0);
    for (int i = 0; path_env_var[i]; i++)
        if (path_env_var[i] == ':')
            count++;
    return (count);
}

static char **get_paths(env_t const *env)
{
    char *path_var = get_env_var(env, "PATH");
    int count = count_paths(path_var);
    char **paths = malloc(sizeof(char *) * (count + 1));
    int path_i = 0;

    paths[count] = NULL;
    for (int i = 1; i < count; i++) {
        for (; path_var[path_i] != ':' && path_var[path_i] != 0; path_i++);
        path_var[path_i] = 0;
        paths[i] = path_var + path_i + 1;
        path_i++;
    }
    paths[0] = path_var;
    return (paths);
}

char *search_in_path(char *str, env_t *env)
{
    char **paths = get_paths(env);
    char *model[] = {NULL, "/", str, NULL};
    char *real_path = NULL;

    for (int i = 0; paths[i]; i++) {
        model[0] = paths[i];
        real_path = my_strcat(model);
        if (fs_entry_exists(real_path)) {
            free(paths[0]);
            free(paths);
            return (real_path);
        }
        free(real_path);
    }
    free(paths[0]);
    free(paths);
    return (NULL);
}