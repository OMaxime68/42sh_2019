/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** env
*/

#include "env.h"
#include "string_utils.h"
#include <stdlib.h>

static void split_raw(char *in, char** name, char **value)
{
    int split_index = -1;
    int len = my_strlen(in);

    for (int i = 0; in[i]; i++)
        if (in[i] == '=') {
            split_index = i;
            break;
        }
    if (split_index < 0)
        split_index = len - 1;
    *name = malloc(sizeof(char) * split_index + 1);
    *value = malloc(sizeof(char) * (len - split_index));
    for (int i = 0; i < split_index; i++)
        (*name)[i] = in[i];
    (*name)[split_index] = 0;
    for (int i = 0; i < (len - split_index - 1); i++)
        (*value)[i] = in[split_index + 1 + i];
    (*value)[len - split_index - 1] = 0;
}

static void add_env(env_t *env, char **raw_env)
{
    env_node_t* last_node = NULL;
    env_node_t* new_node = NULL;
    char *name;
    char *value;

    for (int i = 0; raw_env[i]; i++) {
        new_node = malloc(sizeof(env_node_t));
        split_raw(raw_env[i], &name, &value);
        new_node->name = name;
        new_node->value = value;
        new_node->next = NULL;
        if (last_node == NULL) {
            last_node = new_node;
            env->first = last_node;
        } else {
            last_node->next = new_node;
            last_node = new_node;
        }
    }
}

env_t *parse_env(char **raw_env)
{
    env_t* res = malloc(sizeof(env_t));

    if (res == NULL)
        return (NULL);
    res->first = NULL;
    res->count = 0;
    for (; raw_env[res->count]; res->count++);
    add_env(res, raw_env);
    return (res);
}

void free_env(env_t *env)
{
    env_node_t *next_node = env->first;
    env_node_t *temp;

    while (next_node != NULL) {
        temp = next_node;
        next_node = temp->next;
        free(temp->name);
        free(temp->value);
        free(temp);
    }
    free(env);
}

char *get_env_var(env_t const *env, char const *name)
{
    env_node_t *it = env->first;

    while (it != NULL) {
        if (my_streq(it->name, name))
            return (my_strdup(it->value));
        it = it->next;
    }
    return (NULL);
}