/*
** EPITECH PROJECT, 2020
** PSU_minishell1_2019
** File description:
** my_str_to_word_array
*/

#include <stdlib.h>
#include <stddef.h>

short is_not_sp(char value)
{
    char *whitespaces = " \t\r\n";

    for (int i = 0; i < 4; i++)
        if (value == whitespaces[i])
            return (0);
    return (1);
}

static int calculate_words_count(char const *str)
{
    int words_count = 1;
    int is_empty = is_not_sp(str[0]) ? 0 : 1;

    for (int i = 1; str[i]; i++) {
        if (!is_not_sp(str[i]) && is_not_sp(str[i - 1]))
            words_count++;
        if (is_not_sp(str[i]))
            is_empty = 0;
    }
    if (is_empty)
        return (0);
    return (words_count);
}

static char *create_word(char const *str, int start_index, int end_index)
{
    char *word = malloc(sizeof(char) * (end_index - start_index + 2));
    int word_index = 0;

    for (int i = start_index; i <= end_index; i++) {
        word[word_index] = str[i];
        word_index++;
    }
    word[word_index] = '\0';
    return (word);
}

static int get_last_word_index(char const *str)
{
    int last_word_index = 0;

    for (int i = 0; str[i]; i++) {
        if (is_not_sp(str[i]))
            last_word_index = i;
    }
    return (last_word_index);
}

char **my_str_to_word_array(char const *str)
{
    int words_count = calculate_words_count(str) + 1;
    int last_words_index = get_last_word_index(str);
    int words_index = 0;
    int word_si = 0;
    char **words = malloc(sizeof(char *) * words_count + 1);

    for (int i = 0; str[i] && i <= last_words_index && words_count > 0; i++) {
        if (!is_not_sp(str[i]) && is_not_sp(str[i - 1])) {
            words[words_index] = create_word(str, word_si, i - 1);
            word_si = i + 1;
            words_index++;
        } else if (!is_not_sp(str[i]) && !is_not_sp(str[i - 1]))
            word_si++;
    }
    if (words_count > 1) {
        words[words_index] = create_word(str, word_si, last_words_index);
        words[words_index + 1] = NULL;
    } else
        words[0] = NULL;
    return (words);
}
