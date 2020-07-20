/*
** EPITECH PROJECT, 2020
** PSU_42sh_2019
** File description:
** command_wait
*/

#include "command.h"
#include <sys/wait.h>

static void add_to_arr(int pid, stat_t *stat)
{
    int i = 0;

    while (stat->pid_to_wait[i] > 0)
        i++;
    stat->pid_to_wait[i] = pid;
    stat->pid_to_wait[i + 1] = -1;
}

static void end_one(int pid)
{
    int status;

    waitpid(pid, &status, WUNTRACED);
    print_command_error(status);
}

static void end_arr(stat_t *stat)
{
    for (int i = 0; stat->pid_to_wait[i] > 0; i++)
        if (stat->pid_to_wait[i + 1] < 0)
            end_one(stat->pid_to_wait[i]);
    stat->pid_to_wait[0] = -1;
}

void handle_command_wait(int pid, int end, stat_t *stat)
{
    add_to_arr(pid, stat);
    if (end)
        end_arr(stat);
}
