/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** command_run
*/

#include "command.h"
#include "my_puts.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

static int handle_output(command_t *com, stat_t *stat)
{
    int output = 1;

    if (com->output_mode == 1)
        output = open(com->file_output, O_WRONLY | O_CREAT, 0600);
    if (com->output_mode == 2)
        output = open(com->file_output, O_WRONLY | O_APPEND | O_CREAT, 0600);
    if (com->output_mode == 3)
        output = com->output_fd;
    if (output < 0) {
            my_puterr(com->file_output);
            my_puterr(": ");
            my_puterr(strerror(errno));
            my_puterr("\n");
            return (0);
    }
    if (output != 1) {
        dup2(output, 1);
        close(output);
    }
    return (1);
}

static int handle_input(command_t *com, stat_t *stat)
{
    int input = 0;

    if (com->input_mode == 1 && com->file_input != NULL) {
        input = open(com->file_input, O_RDONLY);
        if (input < 0) {
            my_puterr(com->file_input);
            my_puterr(": ");
            my_puterr(strerror(errno));
            my_puterr("\n");
            return (0);
        }
    }
    if (com->input_mode == 2 && stat->pipe >= 0)
        input = com->input_fd;
    if (input != 0) {
        dup2(input, 0);
        close(input);
    }
    return (1);
}

static int make_pipe(command_t *com, stat_t* stat)
{
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        stat->should_quit = 0;
        return (-1);
    }
    com->output_fd = pipefd[1];
    stat->pipe = pipefd[0];
    return (0);
}

static void run(command_t *com, stat_t *stat)
{
    char **raw_env;

    stat->should_quit = 0;
    raw_env = to_raw_env(stat->env);
    if (handle_input(com, stat) && handle_output(com, stat))
        execve(com->exec, com->av, raw_env);
    free_raw_env(raw_env);
}

void exec_command(command_t *com, stat_t *stat)
{
    pid_t pid;

    com->input_fd = stat->pipe;
    if (com->output_mode == 3 && make_pipe(com, stat) == -1)
        return;
    pid = fork();
    if (pid == 0)
        run(com, stat);
    else {
        if (com->output_mode == 3)
            close(com->output_fd);
        handle_command_wait(pid, com->output_mode != 3, stat);
    }
}
