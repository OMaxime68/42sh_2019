/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** stat
*/

#pragma once

#include "env.h"

typedef struct stat_s
{
    env_t *env;
    int pipe;
    int pid_to_wait[32];
    int should_quit;
} stat_t;

stat_t *init_stat(char **);
void free_stat(stat_t *);
