/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** command
*/

#pragma once

#include "stat.h"

typedef struct
{
    char *exec;
    char **av;
    int output_mode;
    int input_mode;
    char *file_output;
    char *file_input;
    int output_fd;
    int input_fd;
} command_t;

char *get_command_at(char **commands, int i);
void run_command(char **commands, int i, stat_t *stat);
void build_command(command_t *command, char **commands, int i);
void exec_command(command_t *com, stat_t *stat);
void handle_command_wait(int pid, int end, stat_t *stat);
void print_command_error(int status);
