/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** env
*/

#pragma once

typedef struct env_node_s
{
    char *name;
    char *value;
    struct env_node_s *next;
} env_node_t;

typedef struct env_s
{
    env_node_t *first;
    int count;
} env_t;

env_t *parse_env(char **);
void free_env(env_t*);
char **to_raw_env(env_t const *);
void free_raw_env(char **);
char *get_env_var(env_t const *, char const *);