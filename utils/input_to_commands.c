/*
** EPITECH PROJECT, 2020
** PSU_minishell2_2019
** File description:
** input_to_commands
*/

#include "input_to_commands.h"
#include "string_utils.h"
#include "my_str_to_word_array.h"
#include <stdlib.h>

static int start_with_str(char *a, char *b)
{
    int len_a = my_strlen(a);
    int len_b = my_strlen(b);

    if (len_a < len_b)
        return (0);
    for (int i = 0; i < len_b; i++)
        if (a[i] != b[i])
            return (0);
    return (1);
}

int starts_with_splitter(char *str)
{
    char *splitters[] = {"|", ";", "<<", ">>", ">", "<", NULL};

    for (int i = 0; splitters[i]; i++)
        if (start_with_str(str, splitters[i]))
            return (my_strlen(splitters[i]));
    return (0);
}

static char *substr(char *str, int start, int end)
{
    int len = end - start + 1;
    char *new = malloc(len + 1);

    while (!is_not_sp(str[start]) && len > 0) {
        start++;
        len--;
    }
    while (!is_not_sp(str[end]) && len > 0) {
        end--;
        len--;
    }
    for (int i = 0; i < len; i++)
        new[i] = str[i + start];
    new[len] = 0;
    return (new);
}

char **input_to_commands(char *input)
{
    char **commands = malloc(sizeof(char *) * 100);
    int commands_i = 0;
    int splitter_size = 0;
    int start_i = 0;

    for (int i = 0; input[i]; i++) {
        splitter_size = starts_with_splitter(input + i);
        if (splitter_size > 0) {
            commands[commands_i++] = substr(input, start_i, i - 1);
            commands[commands_i++] = substr(input, i, i + splitter_size - 1);
            start_i = i + splitter_size;
            i += splitter_size;
        }
    }
    commands[commands_i++] = substr(input, start_i, my_strlen(input) - 1);
    commands[commands_i] = NULL;
    return (commands);
}
