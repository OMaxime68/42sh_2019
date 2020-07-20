/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** builtins
*/

#pragma once

#include "command.h"
#include "stat.h"

void bi_exit(command_t *, stat_t *);
void bi_env(command_t *, stat_t *);
void bi_setenv(command_t *, stat_t *);
void bi_unsetenv(command_t *, stat_t*);
void bi_execute(command_t *, stat_t *);
void bi_cd(command_t *, stat_t *);
