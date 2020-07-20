/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** command_build
*/

#include "command.h"
#include "my_str_to_word_array.h"
#include "string_utils.h"
#include <stdlib.h>

static void file_output(command_t *command, char **commands, int i)
{
    if (my_streq(get_command_at(commands, i + 1), ">")) {
        command->output_mode = 1;
        command->file_output = get_command_at(commands, i + 2);
    }
    if (my_streq(get_command_at(commands, i + 1), ">>")) {
        command->output_mode = 2;
        command->file_output = get_command_at(commands, i + 2);
    }
}

static void file_input(command_t *command, char **commands, int i)
{
    if (my_streq(get_command_at(commands, i + 1), "<")) {
        command->input_mode = 1;
        command->file_input = get_command_at(commands, i + 2);
    }
}

static void pipe_output(command_t *command, char **commands, int i)
{
    if (my_streq(get_command_at(commands, i + 1), "|")) {
        command->output_mode = 3;
    }
}

static int check_should_leave(char **commands, int i, int counter)
{
    char *splitters[] = {"|", ";", NULL};

    for (int j = 0; j < 2; j++)
        if (commands[i + counter] == NULL ||
        my_streq(commands[i + counter], splitters[j]))
            return (1);
    return (0);
}

void build_command(command_t *command, char **commands, int i)
{
    int counter = 1;
    int should_leave = 0;

    command->av = my_str_to_word_array(commands[i]);
    command->input_mode = 0;
    command->output_mode = 0;
    if (my_streq(get_command_at(commands, i - 1), "|"))
        command->input_mode = 2;
    while (should_leave == 0) {
        should_leave = check_should_leave(commands, i, counter);
        file_output(command, commands, i + counter - 1);
        file_input(command, commands, i + counter - 1);
        pipe_output(command, commands, i + counter - 1);
        counter += 2;
    }
}
